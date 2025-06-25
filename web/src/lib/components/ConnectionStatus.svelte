<script lang="ts">
	import { WifiOff, WifiLow, WifiHigh, Wifi } from "@lucide/svelte"
	import { connected, ping } from "$lib/stores/websocket"
</script>

<div class="mb-12 flex items-center text-xl text-white">
	{#if !connected}
		<WifiOff class="mx-2 text-red-600" />
	{:else if $ping > 300}
		<WifiLow class="mx-2 text-red-600" />
	{:else if $ping > 100}
		<WifiHigh class="mx-2 text-yellow-400" />
	{:else}
		<Wifi class="mx-2 text-green-400" />
	{/if}
	{#if connected}
		<h2>{$ping}</h2>
	{/if}
</div>
