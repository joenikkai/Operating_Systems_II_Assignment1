# Running on Windows via Docker

To run this project on Windows, you need to have **Docker Desktop** installed.

### Using Docker Compose (Recommended)

1. Open a terminal (PowerShell or Command Prompt) in the project directory.
2. Build and run the container:
   ```bash
   docker-compose run scheduler
   ```

### Using Docker CLI

1. Build the image:
   ```bash
   docker build -t srtf_scheduler .
   ```
2. Run the container interactively:
   ```bash
   docker run -it --rm -v ${PWD}:/usr/src/app srtf_scheduler
   ```

### Notes for Windows Users:
* The `-it` flag is mandatory for the `ncurses` UI to work.
* If you use **Git Bash**, you might need to prefix the command with `winpty`:
  ```bash
  winpty docker run -it --rm -v "/$(pwd):/usr/src/app" srtf_scheduler
  ```
* The `query` command will generate `gantt_chart.svg` and `process_table.svg` in the project directory. Because of the volume mapping (`-v`), these files will appear on your Windows host immediately.
