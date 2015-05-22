all:
	mkdir -p output/bin output/conf
	#cp -r ./bin/* output/bin/
	#cp -r ./conf/* output/conf/
	make -C src/lib/wrapsock
	make -f Makefile.app

clean:
	rm -rf output
	make clean -C src/lib/wrapsock
	make clean -f Makefile.app
<<<<<<< HEAD
	aaa
=======
	ccc
>>>>>>> 89f30fd5b24086f2ef265e5f4078757f3e4478c4
	fff
