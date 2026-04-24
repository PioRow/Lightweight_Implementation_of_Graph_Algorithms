all:
	Rscript -e 'roxygen2::roxygenise(".")'
	cd .. && R CMD build LIGA && R CMD INSTALL LIGA_0.0.1.tar.gz

clean:
	rm -f src/*.o src/*.so
	rm -rf LIGA.Rcheck
