import { defineConfig } from "vite";

const DEFAULT_PORT = 3000;

// https://vitejs.dev/config/
export default defineConfig({
  server: {
    port: DEFAULT_PORT,
  },
  build: {
    outDir: "build",
    rollupOptions: {
      output: {
        format: "esm",
      },
    },
  },
  esbuild: {
    target: "esnext",
  },
});
