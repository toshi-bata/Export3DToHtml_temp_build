BIN = bin/Export3DToHtml

OBJS = Export3DToHtml/Export3DToHtml.cpp Export3DToHtml/HtmlTemplateBuilder.cpp
CC = g++ -std=c++11
HPUBLISH_DIR = /var/hoops/HOOPS_Exchange_Publish_2025.5.0

PATH_TO_INCLUDES = -I $(HPUBLISH_DIR)/include \
	-D HOOPS_BINARY_DIRECTORY=\"\" \
	-D SAMPLES_DATA_DIRECTORY=\"$(HPUBLISH_DIR)/samples/data\" \
	-D SAMPLES_DATA_HTML_DIRECTORY=\"$(HPUBLISH_DIR)/samples/data/html\" \
	-D SAMPLES_DEFAULT_OUTPUT_PATH=\"../\" \
	-D SAMPLES_PUBLISH_GALLERY_DIRECTORY=\"$(HPUBLISH_DIR)/samples/publish/publishgallery\" \
	-D SAMPLES_PUBLISH_QUICKSTARTS_DIRECTORY=\"$(HPUBLISH_DIR)/samples/publish/publishquickstarts\" \
	-D SAMPLES_PUBLISH_HTML_DIRECTORY=\"$(HPUBLISH_DIR)/samples/publish/publishhtml\" \
	-D SAMPLES_ADOBE_RESOURCE_DIRECTORY=\"../resource\" \
	-D MAX_PATH=260 \

LDLIBS = -ldl -lstdc++ \
	 -lstdc++fs

$(BIN): $(OBJS)
	$(CC) $(PATH_TO_INCLUDES) $(OBJS) -o $(BIN) $(LDLIBS)

.PHONY: clean
clean:
	rm -f $(BIN)