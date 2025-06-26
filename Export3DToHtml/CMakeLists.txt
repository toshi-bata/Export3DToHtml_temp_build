add_executable(Export3DToHtml)

target_include_directories(Export3DToHtml PRIVATE ./)
target_link_libraries(Export3DToHtml PRIVATE hoops::samples)
target_sources(Export3DToHtml
	PRIVATE
		Export3DToHtml.cpp
)