<script lang="ts">
	import { Maximize2 as Maximize, Minimize2 as Minimize } from "@lucide/svelte"
	import { onMount } from "svelte"

	let isFullscreen = false

	function enterFullscreen(): void {
		const el = document.documentElement as HTMLElement & {
			webkitRequestFullscreen?: () => Promise<void>
			msRequestFullscreen?: () => Promise<void>
		}

		if (el.requestFullscreen) {
			el.requestFullscreen()
		} else if (el.webkitRequestFullscreen) {
			el.webkitRequestFullscreen()
		} else if (el.msRequestFullscreen) {
			el.msRequestFullscreen()
		}
	}

	function exitFullscreen(): void {
		const doc = document as Document & {
			webkitExitFullscreen?: () => Promise<void>
			msExitFullscreen?: () => Promise<void>
		}

		if (doc.exitFullscreen) {
			doc.exitFullscreen()
		} else if (doc.webkitExitFullscreen) {
			doc.webkitExitFullscreen()
		} else if (doc.msExitFullscreen) {
			doc.msExitFullscreen()
		}
	}

	function toggleFullscreen(): void {
		if (isFullscreen) {
			exitFullscreen()
		} else {
			enterFullscreen()
		}
	}

	function updateFullscreenState(): void {
		isFullscreen = Boolean(
			document.fullscreenElement ||
				(document as any).webkitFullscreenElement ||
				(document as any).msFullscreenElement
		)
	}

	onMount(() => {
		document.addEventListener("fullscreenchange", updateFullscreenState)
		document.addEventListener("webkitfullscreenchange", updateFullscreenState)
		document.addEventListener("msfullscreenchange", updateFullscreenState)
	})
</script>

<!-- UI -->
<div class="mb-12 flex items-center gap-4 text-4xl font-bold text-white">
	<h1>Sumo Controller</h1>
	<button
		on:click={toggleFullscreen}
		class="rounded-md border border-white p-2 text-white transition hover:border-gray-300 hover:text-gray-300"
		aria-label="Toggle Fullscreen"
	>
		{#if isFullscreen}
			<Minimize size="28px" />
		{:else}
			<Maximize size="28px" />
		{/if}
	</button>
</div>
