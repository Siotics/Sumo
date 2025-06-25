<script lang="ts">
	import '../app.css';

	let { children } = $props();
</script>

<div class=" h-screen w-screen bg-gradient-to-br from-gray-900 to-gray-950">
	{@render children()}
</div>

