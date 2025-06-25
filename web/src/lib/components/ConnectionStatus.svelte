<script lang="ts">
    export let connected: boolean;
    export let ping: number = 999;
  
    import { WifiOff, WifiLow, WifiHigh, Wifi } from "@lucide/svelte";
</script>

<div class="flex items-center text-white mb-12 text-xl">
  {#if !connected}
    <WifiOff class="mx-2 text-red-600" />
    <h2>Disconnected</h2>
  {:else if ping > 300 }
    <WifiLow class="mx-2 text-red-600" />
    <h2>{ping}ms</h2>
  {:else if ping > 100 }
    <WifiHigh class="mx-2 text-yellow-400" />
    <h2>{ping}ms</h2>
  {:else }
    <Wifi class="mx-2 text-green-400" />
    <h2>{ping}ms</h2>
  {/if}
</div>
  