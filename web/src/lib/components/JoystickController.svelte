<script lang="ts">
    import { onMount } from "svelte";
    import { ArrowUp, ArrowDown, ArrowLeft, ArrowRight } from "@lucide/svelte";
  
    let joystickZone: HTMLDivElement | undefined;
  
    let activeDir: "up" | "down" | "left" | "right" | null = null;

    const handleKeyUp = () => {
        activeDir = null;
      };

    const handleKeyDown = (e: KeyboardEvent) => {
        switch (e.key) {
          case "w":
          case "ArrowUp":
            activeDir = "up";
            break;
          case "s":
          case "ArrowDown":
            activeDir = "down";
            break;
          case "a":
          case "ArrowLeft":
            activeDir = "left";
            break;
          case "d":
          case "ArrowRight":
            activeDir = "right";
            break;
        }
      };
  
    onMount(async () => {
      const nipplejs = (await import("nipplejs")).default;
      const manager = nipplejs.create({
        zone: joystickZone,
        mode: "static",
        position: { left: "50%", top: "50%" },
        color: "white",
        size: 100,
        restOpacity: 0.5,
      });
  
      manager.on("move", (evt, data) => {
        if (!data || !data.direction) return;
        console.log("Joystick moving:", data.direction.angle);
      });
  
      manager.on("end", () => {
        console.log("Joystick released");
      });
  
      window.addEventListener("keydown", handleKeyDown);
      window.addEventListener("keyup", handleKeyUp);
    });
  </script>
  
  <style>
    .active {
      background-color: white;
      color: #1f2937;
    }
  </style>
  
  <div class="flex items-center justify-center">
    <div class="relative">
      <div class="w-64 h-64 rounded-full bg-gradient-to-br from-gray-700 to-gray-800 shadow-inner flex items-center justify-center">
        <div bind:this={joystickZone} class="w-32 h-32 rounded-full relative cursor-pointer"></div>
      </div>
  
      <div class="absolute top-4 left-1/2 transform -translate-x-1/2">
        <div class="w-12 h-12 rounded-full border-2 border-white flex items-center justify-center transition-all duration-200 text-white hover:bg-white hover:text-gray-800"
          class:active={activeDir === "up"}>
          <ArrowUp size={20} />
        </div>
      </div>
  
      <div class="absolute bottom-4 left-1/2 transform -translate-x-1/2">
        <div class="w-12 h-12 rounded-full border-2 border-white flex items-center justify-center transition-all duration-200 text-white hover:bg-white hover:text-gray-800"
          class:active={activeDir === "down"}>
          <ArrowDown size={20} />
        </div>
      </div>
  
      <div class="absolute left-4 top-1/2 transform -translate-y-1/2">
        <div class="w-12 h-12 rounded-full border-2 border-white flex items-center justify-center transition-all duration-200 text-white hover:bg-white hover:text-gray-800"
          class:active={activeDir === "left"}>
          <ArrowLeft size={20} />
        </div>
      </div>
  
      <div class="absolute right-4 top-1/2 transform -translate-y-1/2">
        <div class="w-12 h-12 rounded-full border-2 border-white flex items-center justify-center transition-all duration-200 text-white hover:bg-white hover:text-gray-800"
          class:active={activeDir === "right"}>
          <ArrowRight size={20} />
        </div>
      </div>
    </div>
  </div>
  