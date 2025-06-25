<script lang="ts">
	import { User } from "@lucide/svelte"
	import { pilots as count } from "$lib/stores/websocket"
</script>

<div class="mb-12 flex items-center text-xl text-white">
	<User class="mx-2" />
	{#if $count <= 1}
		<h2>{$count} Pilot</h2>
	{:else}
		<h2>{$count} Pilots</h2>
	{/if}
</div>
