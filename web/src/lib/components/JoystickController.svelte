<script lang="ts">
	import { onMount } from "svelte"
	import { ArrowUp, ArrowDown, ArrowLeft, ArrowRight } from "@lucide/svelte"
	import { sendSocket } from "$lib/stores/websocket"

	let joystickZone: HTMLDivElement | undefined

	let activeDir: "up" | "down" | "left" | "right" | null = null

	const handleKeyUp = () => {
		activeDir = null
		sendSocket({ left: 0, right: 0 })
	}

	const handleKeyDown = (e: KeyboardEvent) => {
		switch (e.key) {
			case "w":
			case "ArrowUp":
				handleDirectionPress("up")
				break
			case "s":
			case "ArrowDown":
				handleDirectionPress("down")
				break
			case "a":
			case "ArrowLeft":
				handleDirectionPress("left")
				break
			case "d":
			case "ArrowRight":
				handleDirectionPress("right")
				break
		}
	}

	const handleDirectionPress = (dir: "up" | "down" | "left" | "right") => {
		activeDir = dir
		switch (dir) {
			case "up":
				sendSocket({ left: 1, right: 1 })
				break
			case "down":
				sendSocket({ left: -1, right: -1 })
				break
			case "left":
				sendSocket({ left: 1, right: 0 })
				break
			case "right":
				sendSocket({ left: 0, right: 1 })
				break
		}
	}

	const handleDirectionRelease = () => {
		activeDir = null
		sendSocket({ left: 0, right: 0 })
	}

	onMount(async () => {
		const nipplejs = (await import("nipplejs")).default
		const manager = nipplejs.create({
			zone: joystickZone,
			mode: "static",
			position: { left: "50%", top: "50%" },
			color: "white",
			size: 100,
			restOpacity: 0.5
		})

		manager.on("move", (evt, data) => {
			if (!data || !data.direction) return
			const x = data.vector.x
			const y = data.vector.y

			let left = y + x
			let right = y - x

			const max = Math.max(Math.abs(left), Math.abs(right), 1)
			left /= max
			right /= max

			sendSocket({ left, right })
		})

		manager.on("end", () => {
			console.log("Joystick released")
			sendSocket({ left: 0, right: 0 })
		})

		window.addEventListener("keydown", handleKeyDown)
		window.addEventListener("keyup", handleKeyUp)
	})
</script>

<div class="flex items-center justify-center">
	<div class="relative">
		<!-- Joystick -->
		<div
			class="flex h-64 w-64 items-center justify-center rounded-full bg-gradient-to-br from-gray-700 to-gray-800 shadow-inner"
		>
			<div bind:this={joystickZone} class="relative h-32 w-32 cursor-pointer rounded-full"></div>
		</div>

		<!-- UP -->
		<div class="absolute top-4 left-1/2 -translate-x-1/2 transform">
			<div
				role="button"
				tabindex="0"
				class="flex h-12 w-12 items-center justify-center rounded-full border-2 border-white text-white transition-all duration-200 hover:bg-white hover:text-gray-800"
				class:active={activeDir === "up"}
				on:touchstart={() => handleDirectionPress("up")}
				on:touchend={handleDirectionRelease}
				on:mousedown={() => handleDirectionPress("up")}
				on:mouseup={handleDirectionRelease}
				on:mouseleave={handleDirectionRelease}
			>
				<ArrowUp size={20} />
			</div>
		</div>

		<!-- DOWN -->
		<div class="absolute bottom-4 left-1/2 -translate-x-1/2 transform">
			<div
				role="button"
				tabindex="0"
				class="flex h-12 w-12 items-center justify-center rounded-full border-2 border-white text-white transition-all duration-200 hover:bg-white hover:text-gray-800"
				class:active={activeDir === "down"}
				on:touchstart={() => handleDirectionPress("down")}
				on:touchend={handleDirectionRelease}
				on:mousedown={() => handleDirectionPress("down")}
				on:mouseup={handleDirectionRelease}
				on:mouseleave={handleDirectionRelease}
			>
				<ArrowDown size={20} />
			</div>
		</div>

		<!-- LEFT -->
		<div class="absolute top-1/2 left-4 -translate-y-1/2 transform">
			<div
				role="button"
				tabindex="0"
				class="flex h-12 w-12 items-center justify-center rounded-full border-2 border-white text-white transition-all duration-200 hover:bg-white hover:text-gray-800"
				class:active={activeDir === "left"}
				on:touchstart={() => handleDirectionPress("left")}
				on:touchend={handleDirectionRelease}
				on:mousedown={() => handleDirectionPress("left")}
				on:mouseup={handleDirectionRelease}
				on:mouseleave={handleDirectionRelease}
			>
				<ArrowLeft size={20} />
			</div>
		</div>

		<!-- RIGHT -->
		<div class="absolute top-1/2 right-4 -translate-y-1/2 transform">
			<div
				role="button"
				tabindex="0"
				class="flex h-12 w-12 items-center justify-center rounded-full border-2 border-white text-white transition-all duration-200 hover:bg-white hover:text-gray-800"
				class:active={activeDir === "right"}
				on:touchstart={() => handleDirectionPress("right")}
				on:touchend={handleDirectionRelease}
				on:mousedown={() => handleDirectionPress("right")}
				on:mouseup={handleDirectionRelease}
				on:mouseleave={handleDirectionRelease}
			>
				<ArrowRight size={20} />
			</div>
		</div>
	</div>
</div>

<style>
	.active {
		background-color: white;
		color: #1f2937;
	}
</style>
