<script>
	import JoystickController from "$lib/components/JoystickController.svelte"
	import Header from "$lib/components/Header.svelte"
	import ConnectionStatus from "$lib/components/ConnectionStatus.svelte"
	import PilotIndicator from "$lib/components/PilotIndicator.svelte"
</script>

<div class="flex h-screen w-full flex-col items-center justify-center">
	<Header />
	<div class="flex gap-4">
		<ConnectionStatus />
		<PilotIndicator />
	</div>
	<JoystickController />
</div>
