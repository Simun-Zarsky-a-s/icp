all: qMakeFile
	@echo "Making ..."
	make -f qMakeFile


qMakeFile: Pacman.pro
	@echo "Making qMakeFile"
	qmake -o qMakeFile Pacman.pro


clean:
	-rm .qmake.stash moc_* qrc_* qMakeFile