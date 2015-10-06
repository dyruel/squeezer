
default: release

release:
	cmake -E make_directory build
	cmake -E chdir build/ cmake -G"Unix Makefiles" ../src
	cmake -E chdir build/ make
	
doc:
	cmake -E time doxygen
	
clean_build:
	cmake -E remove_directory build

clean_doc:
	cmake -E remove_directory docs/latex
	cmake -E remove_directory docs/html
	cmake -E remove -f docs/squeezer.tag docs/warning.txt

clean: clean_build clean_doc