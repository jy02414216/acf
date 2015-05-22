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
	aaa
	fff
