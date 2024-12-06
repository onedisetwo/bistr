# include <stdio.h>

# include "geometry.h"
# include "status.h"
//# include <fstream>

int main (int argc, char *argv[]) {
	int n;
	R2::Polygon m_polygon;
	R2::Point viewpoint;
	if(argc == 1) {
//		printf("Input number of vertices: ");
//		scanf("%d", &n);
//		printf("%d\n", n);

		if(!m_polygon.read().good())
			return -1;
		printf("\n");
		m_polygon.print();
		printf("\nEnter viewpoint:\n");
		if(!viewpoint.read().good())
			return -1;
		printf("\n");
		viewpoint.print();
		printf("\nAnswer: %lf\n", m_polygon.get_view_angle(viewpoint));
		return 0;
	}
	if(argc == 2) {
		char* filename = argv[1];
		FILE *fp;
		if(!(fp = fopen(filename, "r")))
			return -1;
		if(!m_polygon.read(fp, false).good() || !viewpoint.read(fp, false).good()){
			fclose(fp);
			return -1;
		}
		printf("Answer: %lf\n", m_polygon.get_view_angle(viewpoint));
		fclose(fp);
		return 0;
	}
	if(argc > 2){
		printf("Usage error\n");
		return 0;
	}
}
