CXXFLAGS = -Wall -pedantic -std=c++14
USERNAME = kollepe1
HEADERS = $(wildcard src/*.h) $(wildcard src/*/*.h)
SOURCES = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJECTS = $(SOURCES:src/%.cpp=build/%.o)

.PHONY: all
all: compile doc

#compile and start the program
.PHONY: run
run: compile
	./$(USERNAME)

#tesging asserts in main.cpp
.PHONY: testing
testing: CXXFLAGS += -D TESTING
testing: compile
	mv $(USERNAME) $@
	./$@

.PHONY: compile
compile: $(USERNAME)

#links the final file and renames it as USERNAME
.PHONY: $(USERNAME)
$(USERNAME): build/main
	cp $< $@

build/main: $(OBJECTS)
	mkdir -p $(@D)
	g++ $^ -o $@

#compiles all .o files without linking
build/%.o: src/%.cpp
	mkdir -p $(@D)
	g++ $(CXXFLAGS) $< -c -o $@

doc: Doxyfile $(HEADERS)
	doxygen Doxyfile

#Cleans unnecessary files
.PHONY: clean
clean:
	rm -rf $(USERNAME) testing doc/ build/ 2>/dev/null

#DEPENDENCIES g++ -MM src/*/*.cpp | sed 's|^C|build/C|'; g++ -MM src/*.cpp | sed 's|^m|build/m|'
build/CApplication.o: src/Application/CApplication.cpp \
 src/Application/CApplication.h src/Application/../Calendar/CCalendar.h \
 src/Application/../Calendar/../Date/CDate.h \
 src/Application/../Calendar/../Event/CEvent.h \
 src/Application/../Calendar/../Event/../Validator/CValidator.h \
 src/Application/../Calendar/../Event/../Prompt/CPrompt.h \
 src/Application/../Command/CCommand.h \
 src/Application/../Command/../DisplayMode/CDisplayMode.h \
 src/Application/../InputHandler/CInputHandler.h \
 src/Application/../DisplayMode/CDisplayMonth.h
build/CCalendar.o: src/Calendar/CCalendar.cpp src/Calendar/CCalendar.h \
 src/Calendar/../Date/CDate.h src/Calendar/../Event/CEvent.h \
 src/Calendar/../Event/../Validator/CValidator.h \
 src/Calendar/../Event/../Prompt/CPrompt.h
build/CAddEvent.o: src/Command/CAddEvent.cpp src/Command/CAddEvent.h \
 src/Command/CCommand.h src/Command/../Calendar/CCalendar.h \
 src/Command/../Calendar/../Date/CDate.h \
 src/Command/../Calendar/../Event/CEvent.h \
 src/Command/../Calendar/../Event/../Validator/CValidator.h \
 src/Command/../Calendar/../Event/../Prompt/CPrompt.h \
 src/Command/../DisplayMode/CDisplayMode.h \
 src/Command/../Event/CRecurringEvent.h
build/CChangeDisplayMode.o: src/Command/CChangeDisplayMode.cpp \
 src/Command/CChangeDisplayMode.h src/Command/CCommand.h \
 src/Command/../Calendar/CCalendar.h \
 src/Command/../Calendar/../Date/CDate.h \
 src/Command/../Calendar/../Event/CEvent.h \
 src/Command/../Calendar/../Event/../Validator/CValidator.h \
 src/Command/../Calendar/../Event/../Prompt/CPrompt.h \
 src/Command/../DisplayMode/CDisplayMode.h \
 src/Command/../DisplayMode/CDisplayWeek.h \
 src/Command/../DisplayMode/CDisplayDay.h \
 src/Command/../DisplayMode/CDisplayMonth.h
build/CCommand.o: src/Command/CCommand.cpp src/Command/./CCommand.h \
 src/Command/./../Calendar/CCalendar.h \
 src/Command/./../Calendar/../Date/CDate.h \
 src/Command/./../Calendar/../Event/CEvent.h \
 src/Command/./../Calendar/../Event/../Validator/CValidator.h \
 src/Command/./../Calendar/../Event/../Prompt/CPrompt.h \
 src/Command/./../DisplayMode/CDisplayMode.h
build/CDraw.o: src/Command/CDraw.cpp src/Command/CDraw.h src/Command/CCommand.h \
 src/Command/../Calendar/CCalendar.h \
 src/Command/../Calendar/../Date/CDate.h \
 src/Command/../Calendar/../Event/CEvent.h \
 src/Command/../Calendar/../Event/../Validator/CValidator.h \
 src/Command/../Calendar/../Event/../Prompt/CPrompt.h \
 src/Command/../DisplayMode/CDisplayMode.h
build/CExit.o: src/Command/CExit.cpp src/Command/CExit.h src/Command/CCommand.h \
 src/Command/../Calendar/CCalendar.h \
 src/Command/../Calendar/../Date/CDate.h \
 src/Command/../Calendar/../Event/CEvent.h \
 src/Command/../Calendar/../Event/../Validator/CValidator.h \
 src/Command/../Calendar/../Event/../Prompt/CPrompt.h \
 src/Command/../DisplayMode/CDisplayMode.h
build/CExport.o: src/Command/CExport.cpp src/Command/CExport.h \
 src/Command/CCommand.h src/Command/../Calendar/CCalendar.h \
 src/Command/../Calendar/../Date/CDate.h \
 src/Command/../Calendar/../Event/CEvent.h \
 src/Command/../Calendar/../Event/../Validator/CValidator.h \
 src/Command/../Calendar/../Event/../Prompt/CPrompt.h \
 src/Command/../DisplayMode/CDisplayMode.h
build/CFindEvent.o: src/Command/CFindEvent.cpp src/Command/CFindEvent.h \
 src/Command/CCommand.h src/Command/../Calendar/CCalendar.h \
 src/Command/../Calendar/../Date/CDate.h \
 src/Command/../Calendar/../Event/CEvent.h \
 src/Command/../Calendar/../Event/../Validator/CValidator.h \
 src/Command/../Calendar/../Event/../Prompt/CPrompt.h \
 src/Command/../DisplayMode/CDisplayMode.h \
 src/Command/../Operation/COperation.h src/Command/../Operation/CRemove.h \
 src/Command/../Operation/CEdit.h src/Command/../Operation/CMove.h \
 src/Command/../Operation/../MoveStrategy/CMoveStrategy.h
build/CImport.o: src/Command/CImport.cpp src/Command/CImport.h \
 src/Command/CCommand.h src/Command/../Calendar/CCalendar.h \
 src/Command/../Calendar/../Date/CDate.h \
 src/Command/../Calendar/../Event/CEvent.h \
 src/Command/../Calendar/../Event/../Validator/CValidator.h \
 src/Command/../Calendar/../Event/../Prompt/CPrompt.h \
 src/Command/../DisplayMode/CDisplayMode.h src/Command/CAddEvent.h \
 src/Command/../Event/CRecurringEvent.h
build/CNextPeriod.o: src/Command/CNextPeriod.cpp src/Command/CNextPeriod.h \
 src/Command/CCommand.h src/Command/../Calendar/CCalendar.h \
 src/Command/../Calendar/../Date/CDate.h \
 src/Command/../Calendar/../Event/CEvent.h \
 src/Command/../Calendar/../Event/../Validator/CValidator.h \
 src/Command/../Calendar/../Event/../Prompt/CPrompt.h \
 src/Command/../DisplayMode/CDisplayMode.h
build/CPrevPeriod.o: src/Command/CPrevPeriod.cpp src/Command/CPrevPeriod.h \
 src/Command/CCommand.h src/Command/../Calendar/CCalendar.h \
 src/Command/../Calendar/../Date/CDate.h \
 src/Command/../Calendar/../Event/CEvent.h \
 src/Command/../Calendar/../Event/../Validator/CValidator.h \
 src/Command/../Calendar/../Event/../Prompt/CPrompt.h \
 src/Command/../DisplayMode/CDisplayMode.h
build/CDate.o: src/Date/CDate.cpp src/Date/CDate.h
build/CDisplayDay.o: src/DisplayMode/CDisplayDay.cpp \
 src/DisplayMode/CDisplayDay.h src/DisplayMode/CDisplayMode.h \
 src/DisplayMode/../Date/CDate.h src/DisplayMode/../Event/CEvent.h \
 src/DisplayMode/../Event/../Validator/CValidator.h \
 src/DisplayMode/../Event/../Prompt/CPrompt.h \
 src/DisplayMode/../Calendar/CCalendar.h
build/CDisplayMode.o: src/DisplayMode/CDisplayMode.cpp \
 src/DisplayMode/./CDisplayMode.h src/DisplayMode/./../Date/CDate.h \
 src/DisplayMode/./../Event/CEvent.h \
 src/DisplayMode/./../Event/../Validator/CValidator.h \
 src/DisplayMode/./../Event/../Prompt/CPrompt.h \
 src/DisplayMode/./../Calendar/CCalendar.h
build/CDisplayMonth.o: src/DisplayMode/CDisplayMonth.cpp \
 src/DisplayMode/CDisplayMonth.h src/DisplayMode/CDisplayMode.h \
 src/DisplayMode/../Date/CDate.h src/DisplayMode/../Event/CEvent.h \
 src/DisplayMode/../Event/../Validator/CValidator.h \
 src/DisplayMode/../Event/../Prompt/CPrompt.h \
 src/DisplayMode/../Calendar/CCalendar.h
build/CDisplayWeek.o: src/DisplayMode/CDisplayWeek.cpp \
 src/DisplayMode/CDisplayWeek.h src/DisplayMode/CDisplayMode.h \
 src/DisplayMode/../Date/CDate.h src/DisplayMode/../Event/CEvent.h \
 src/DisplayMode/../Event/../Validator/CValidator.h \
 src/DisplayMode/../Event/../Prompt/CPrompt.h \
 src/DisplayMode/../Calendar/CCalendar.h
build/CEvent.o: src/Event/CEvent.cpp src/Event/CEvent.h \
 src/Event/../Date/CDate.h src/Event/../Validator/CValidator.h \
 src/Event/../Prompt/CPrompt.h
build/CRecurringEvent.o: src/Event/CRecurringEvent.cpp \
 src/Event/CRecurringEvent.h src/Event/CEvent.h src/Event/../Date/CDate.h \
 src/Event/../Validator/CValidator.h src/Event/../Prompt/CPrompt.h
build/CInputHandler.o: src/InputHandler/CInputHandler.cpp \
 src/InputHandler/CInputHandler.h src/InputHandler/../Date/CDate.h \
 src/InputHandler/../Command/CCommand.h \
 src/InputHandler/../Command/../Calendar/CCalendar.h \
 src/InputHandler/../Command/../Calendar/../Event/CEvent.h \
 src/InputHandler/../Command/../Calendar/../Event/../Validator/CValidator.h \
 src/InputHandler/../Command/../Calendar/../Event/../Prompt/CPrompt.h \
 src/InputHandler/../Command/../DisplayMode/CDisplayMode.h \
 src/InputHandler/../Command/CDraw.h \
 src/InputHandler/../Command/CNextPeriod.h \
 src/InputHandler/../Command/CPrevPeriod.h \
 src/InputHandler/../Command/CExit.h \
 src/InputHandler/../Command/CChangeDisplayMode.h \
 src/InputHandler/../Command/CFindEvent.h \
 src/InputHandler/../Command/../Operation/COperation.h \
 src/InputHandler/../Command/CAddEvent.h \
 src/InputHandler/../Command/../Event/CRecurringEvent.h \
 src/InputHandler/../Command/CImport.h \
 src/InputHandler/../Command/CExport.h
build/CClosestDaySameTime.o: src/MoveStrategy/CClosestDaySameTime.cpp \
 src/MoveStrategy/CClosestDaySameTime.h src/MoveStrategy/CMoveStrategy.h \
 src/MoveStrategy/../Date/CDate.h \
 src/MoveStrategy/../Calendar/CCalendar.h \
 src/MoveStrategy/../Calendar/../Event/CEvent.h \
 src/MoveStrategy/../Calendar/../Event/../Validator/CValidator.h \
 src/MoveStrategy/../Calendar/../Event/../Prompt/CPrompt.h
build/CMoveStrategy.o: src/MoveStrategy/CMoveStrategy.cpp \
 src/MoveStrategy/CMoveStrategy.h src/MoveStrategy/../Date/CDate.h \
 src/MoveStrategy/../Calendar/CCalendar.h \
 src/MoveStrategy/../Calendar/../Event/CEvent.h \
 src/MoveStrategy/../Calendar/../Event/../Validator/CValidator.h \
 src/MoveStrategy/../Calendar/../Event/../Prompt/CPrompt.h
build/CSpecificDateSameTime.o: src/MoveStrategy/CSpecificDateSameTime.cpp \
 src/MoveStrategy/CSpecificDateSameTime.h \
 src/MoveStrategy/CMoveStrategy.h src/MoveStrategy/../Date/CDate.h \
 src/MoveStrategy/../Calendar/CCalendar.h \
 src/MoveStrategy/../Calendar/../Event/CEvent.h \
 src/MoveStrategy/../Calendar/../Event/../Validator/CValidator.h \
 src/MoveStrategy/../Calendar/../Event/../Prompt/CPrompt.h
build/CEdit.o: src/Operation/CEdit.cpp src/Operation/CEdit.h \
 src/Operation/COperation.h src/Operation/../Event/CEvent.h \
 src/Operation/../Event/../Date/CDate.h \
 src/Operation/../Event/../Validator/CValidator.h \
 src/Operation/../Event/../Prompt/CPrompt.h \
 src/Operation/../Calendar/CCalendar.h
build/CMove.o: src/Operation/CMove.cpp src/Operation/CMove.h \
 src/Operation/COperation.h src/Operation/../Event/CEvent.h \
 src/Operation/../Event/../Date/CDate.h \
 src/Operation/../Event/../Validator/CValidator.h \
 src/Operation/../Event/../Prompt/CPrompt.h \
 src/Operation/../Calendar/CCalendar.h \
 src/Operation/../MoveStrategy/CMoveStrategy.h \
 src/Operation/../MoveStrategy/CClosestDaySameTime.h \
 src/Operation/../MoveStrategy/CSpecificDateSameTime.h
build/COperation.o: src/Operation/COperation.cpp src/Operation/COperation.h \
 src/Operation/../Event/CEvent.h src/Operation/../Event/../Date/CDate.h \
 src/Operation/../Event/../Validator/CValidator.h \
 src/Operation/../Event/../Prompt/CPrompt.h \
 src/Operation/../Calendar/CCalendar.h
build/CRemove.o: src/Operation/CRemove.cpp src/Operation/CRemove.h \
 src/Operation/COperation.h src/Operation/../Event/CEvent.h \
 src/Operation/../Event/../Date/CDate.h \
 src/Operation/../Event/../Validator/CValidator.h \
 src/Operation/../Event/../Prompt/CPrompt.h \
 src/Operation/../Calendar/CCalendar.h
build/CPrompt.o: src/Prompt/CPrompt.cpp src/Prompt/CPrompt.h \
 src/Prompt/../Validator/CValidator.h \
 src/Prompt/../Validator/../Date/CDate.h
build/CValidator.o: src/Validator/CValidator.cpp src/Validator/CValidator.h \
 src/Validator/../Date/CDate.h
build/main.o: src/main.cpp src/./Application/CApplication.h \
 src/./Application/../Calendar/CCalendar.h \
 src/./Application/../Calendar/../Date/CDate.h \
 src/./Application/../Calendar/../Event/CEvent.h \
 src/./Application/../Calendar/../Event/../Validator/CValidator.h \
 src/./Application/../Calendar/../Event/../Prompt/CPrompt.h \
 src/./Application/../Command/CCommand.h \
 src/./Application/../Command/../DisplayMode/CDisplayMode.h \
 src/./Application/../InputHandler/CInputHandler.h \
 src/./Application/../DisplayMode/CDisplayMonth.h
