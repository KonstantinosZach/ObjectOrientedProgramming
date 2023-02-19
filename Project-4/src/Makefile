JFLAGS = -g	-Werror
JC = javac

.SUFFIXES: .java .class

.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
		App/Main.java \
		Humans/*.java\
		Structure/*.java\
		InputData/*.java\

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) App/*.class
	$(RM) Humans/*.class
	$(RM) Structure/*.class
	$(RM) InputData/*.class

#command line argumets δίπλα από το App/Main	
run:
	java App/Main  2 3 5 8 2