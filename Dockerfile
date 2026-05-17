# Use an official GCC image as a parent image
FROM gcc:latest

# Set the working directory in the container
WORKDIR /usr/src/app

# Install ncurses library
RUN apt-get update && apt-get install -y libncurses5-dev libncursesw5-dev

# Copy the current directory contents into the container at /usr/src/app
COPY . .

# Compile the project
RUN make clean && make

# Command to run the application
# We use -it with docker run to interact with the ncurses UI
CMD ["./Operating_Systems_II_Assignment1"]
