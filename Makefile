src = $(wildcard src/*.cpp)
flags = -Wall -Wextra -fanalyzer -Os
includes = -I include

app: $(src)
	g++ $(src) $(flags) $(includes) -o app

image.ppm: app
	./app > image.ppm

run: image.ppm

clean:
	rm app image.ppm
