BIN = bin/Export3DToHtml

OBJS = Export3DToHtml/Export3DToHtml.cpp Export3DToHtml/HtmlTemplateBuilder.cpp
CC = g++ -std=c++11

PATH_TO_INCLUDES = -I /var/hoops/HOOPS_Exchange_2025.4.0/include

LDLIBS = -ldl -lstdc++ \
	 -lstdc++fs

$(BIN): $(OBJS)
	$(CC) $(PATH_TO_INCLUDES) $(OBJS) -o $(BIN) $(LDLIBS)

.PHONY: clean
clean:
	rm -f $(BIN)