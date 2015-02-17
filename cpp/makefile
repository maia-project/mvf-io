test:
	g++ test.cpp mvfio.cpp -o test

test-opencv:
	g++ test-opencv.cpp mvfio.cpp `pkg-config opencv --libs --cflags` -o test-opencv

clean:
	rm test test-opencv
