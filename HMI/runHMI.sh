javac -h . *.java

g++ -I /usr/lib/jvm/default-java/include -I /usr/lib/jvm/default-java/include/linux -fPIC -shared HMI_BackE.cpp ../Control_Loop/functions.h ../Control_Loop/stateshandle.cpp -o libHMI_BackE.so

java -Djava.library.path=/home/tped/Desktop/Controls/HMI JavaHMI
