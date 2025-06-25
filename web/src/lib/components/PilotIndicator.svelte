<script lang="ts">
export let count: number = 0;
import { User } from "@lucide/svelte"

</script>

<div class="flex items-center text-xl text-white mb-12">
    <User class="mx-2"/>
    {#if count <= 1}
    <h2>{count} Pilot</h2>
    {:else}
    <h2>{count} Pilots</h2>
    {/if}
</div>