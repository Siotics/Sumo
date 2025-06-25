import { writable } from "svelte/store"
import { z } from "zod/v4"

const PilotsSchema = z.object({
	pilots: z.number()
})

export const connected = writable(false)
export const ping = writable<number>(999)
export const pilots = writable<number>(0)
export const socket = new WebSocket("ws://192.168.4.1/ws")

let pingStart = 0
let pingTimeout: ReturnType<typeof setTimeout> | null = null
let pingInterval: ReturnType<typeof setInterval>

socket.addEventListener("open", () => {
	connected.set(true)
	startPing()
})

socket.addEventListener("close", () => {
	connected.set(false)
	stopPing()
})

socket.addEventListener("message", (event) => {
	const raw = event.data

	if (raw === "pong") {
		const now = performance.now()
		ping.set(Math.round(now - pingStart))
		if (pingTimeout) clearTimeout(pingTimeout)
		return
	}

	try {
		const parsed = JSON.parse(raw)

		if (PilotsSchema.safeParse(parsed).success) {
			pilots.set(parsed.pilots)
		} else {
			console.warn("Unrecognized schema:", parsed)
		}
	} catch (err) {
		console.error("Failed to parse socket message:", raw)
	}
})

export function sendSocket(data: object | string) {
	if (socket.readyState !== WebSocket.OPEN) return
	console.log("sending socket data", data)
	if (typeof data === "object") return socket.send(JSON.stringify(data))
	socket.send(data)
}

function startPing() {
	pingInterval = setInterval(() => {
		if (socket.readyState === WebSocket.OPEN) {
			pingStart = performance.now()
			sendSocket("ping")

			if (pingTimeout) clearTimeout(pingTimeout)
			pingTimeout = setTimeout(() => {
				ping.set(999)
			}, 900)
		}
	}, 1000)
}

function stopPing() {
	clearInterval(pingInterval)
	if (pingTimeout) clearTimeout(pingTimeout)
}
