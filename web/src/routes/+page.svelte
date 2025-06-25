<script>
    import JoystickController from "$lib/components/JoystickController.svelte";
    import Header from "$lib/components/Header.svelte"
	import ConnectionStatus from "$lib/components/ConnectionStatus.svelte";
    import PilotIndicator from "$lib/components/PilotIndicator.svelte";
</script>



<div class="flex flex-col items-center justify-center h-screen w-full">
    <Header />
    <div class="flex gap-4">
        <ConnectionStatus connected={false} ping={200}/>
        <PilotIndicator />
    </div>
    <JoystickController />
</div>
  