# Week 03: Tic-Tac-Toe Game

A classic **Tic-Tac-Toe** game built with **React** and **TypeScript**, featuring a clean and responsive interface, zero layout shifts, and simple state management.

**Live Demo:** [View Tic-Tac-Toe](https://MAXIIIMVS.github.io/weekly_projects/03_react_tic_tac_toe/dist/index.html)

## Features

- 2-player gameplay (X vs O) on the same device
- Fully responsive and centered board
- Clean, modern UI with hover and active effects
- Written in **TypeScript** for type safety

## Quick Start

### Prerequisites

- Node.js (v14 or higher)
- npm or yarn

### Installation

1. Navigate to the project folder:

```bash
cd 03_react_tic_tac_toe
```

2. Install dependencies:

```bash
npm install
```

3. Start the development environment:

```bash
npm run dev
```

4. Open your browser at the URL provided by Vite.

### Production Build

Before building for GitHub Pages, make sure your `vite.config.ts` has:

```ts
import { defineConfig } from "vite";
import react from "@vitejs/plugin-react";

export default defineConfig({
  plugins: [react()],
  base: "./", // ensures assets load correctly in a subfolder
});
```

Then run:

```bash
npm run build
```

The compiled files will be in the `dist/` folder.

---

## Usage

### Playing the Game

1. Click a square to place your mark (**X** or **O**).
2. Players alternate turns automatically.
3. The game displays the **next player**, or announces the **winner** or **DRAW**.

### Resetting the Game

Click the **Reset** button to clear the board and start a new game.

---

This README provides everything you need to start developing, testing, and playing the Week 03 Tic-Tac-Toe Game.
