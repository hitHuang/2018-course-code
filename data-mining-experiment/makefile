INCLUDE=include
main:main.o dataprocess.o decisiontree.o knn.o
	g++ -o main main.o decisiontree.o knn.o dataprocess.o
main.o:main.cpp $(INCLUDE)/decisiontree.h $(INCLUDE)/knn.h
	g++ -c main.cpp
dataprocess.o:dataprocess.cpp $(INCLUDE)/data.h
	g++ -c dataprocess.cpp
decisiontree.o:decisiontree.cpp $(INCLUDE)/decisiontree.h
	g++ -c decisiontree.cpp
knn.o:knn.cpp $(INCLUDE)/knn.h
	g++ -c knn.cpp
clean:
	rm -f *.o main testset.txt trainset.txt
