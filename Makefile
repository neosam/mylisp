OBJS = main.o parser.o eval.o list.o state.o

all: mylisp

mylisp: $(OBJS)
	gcc $(OBJS) -o mylisp

$(OBJS):

clean:
	rm -f $(OBJS) mylisp *~
