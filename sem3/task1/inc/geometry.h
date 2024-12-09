/*!
	\file
	\author Полина Клинова
	\brief Заголовочный файл с реализацией классов Point и Polygon в необходимом для решения задачи объёме
*/

# ifndef GEOMETRY
# define GEOMETRY

# include <cmath>
# include <cstdio>
# include "status.h"

/// Пространство имён геометрических объектов в плоскости
namespace R2 {

	/*!
		\brief Класс, реализующий точку
	*/
	class Point {
		private:
			double x = 0;
			double y = 0;
		public:
			/// Конструктор по умолчанию
			Point () = default;
			/// Деструктор по умолчанию
			~Point () = default;
			/// Конструктор по другой точке
			Point (const Point& p) {
				x = p.x;  y = p.y;
			}
			/// Конструктор по координатам
			Point (double n_x, double n_y) {
				x = n_x;  y = n_y;
			}
			/// Оператор присваивания
			Point& operator= (const Point& p) {
				x = p.x;  y = p.y;
				return *this;
			}
			/*!
				Ввод точки из файлы

				\param fp Файл для ввода (по умолчанию stdin)
				\param is_human {По умолчанию false, при true выводятся сообщения
					о том, что нужно вводить в данный момент}

				\warning Файл должен быть открыт заранее
				\warning Предыдущее содержтмое стирается

				Сначала вводится число вершин, потом координаты каждой
			*/
			Status read (FILE* fp = stdin, bool is_human = false) {
				if(fp == nullptr)
					return Status(err_type::open);
				if(is_human)  printf("Input coordinates: ");
				if(fscanf(fp, "%lf %lf", &x, &y) != 2)
					return Status(err_type::format);
				return Status(err_type::success);
			}
			/// Печать точки
			void print () {
				printf("x: %lf , y: %lf\n", x, y);
			}
			/// Расстояние между точками
			double get_distance (Point& p) const {
				return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
			}
			/// Возвращает угол между Ox и вектором (x, y)
			double get_angle () const {
				return (x != 0 ? atan(y / x) : (y > 0 ? M_PI/2. : -M_PI/2.));
			}
			friend class Polygon;
	} ;

	/*!
		\brief Класс, реализующий многоугольник
	*/
	class Polygon {
		private:
			int n = 0; ///< Число вершин
			Point* vertex = nullptr; ///< Указатель на массив вершин
		public:
			/// Конструктор по умолчанию
			Polygon () = default;
			/// Деструктор
			~Polygon () {
				if(vertex != nullptr)
					delete[] vertex;
			}
			/// Очистка полей класса (с освобождением памяти vertex)
			void clear () {
				n = 0;
				if(vertex != nullptr)
					delete[] vertex;
				vertex = nullptr;
			}
			/*!
				Ввод точек многоугольника из файла

				\param fp Файл для ввода (по умолчанию stdin)
				\param is_human {По умолчанию false, при true выводятся сообщения
					о том, что нужно вводить в данный момент}

				\warning Файл должен быть открыт заранее
				\warning Предыдущее содержтмое стирается

				Сначала вводится число вершин, потом координаты каждой
			*/
			Status read (FILE *fp = stdin, bool is_human = false) {
				if(fp == nullptr)
					return Status(err_type::open);
				if(is_human)  printf("Enter number of vertices: ");
				if(fscanf(fp, "%d", &n) != 1)
					return Status(err_type::format);
				vertex = new Point[n];
				if(is_human)  printf("Enter vertices' coordinates:\n");
				for(int i = 0; i < n; i++){
					if(!vertex[i].read(fp, is_human).good())
						return Status(err_type::format);
				}
				return Status(err_type::success);
			}
			/// Печать данных о многоугольнике в stdout
			void print () const {
				printf("Number of vertices: %d\n", n);
				for(int i = 0; i < n; i++)
					printf("%d: %lf %lf\n", i + 1, vertex[i].x, vertex[i].y);
			}
			/// Решение задачи - нахождение угла, из которого p видит многоугольник
			double get_view_angle (Point& p) {
				double min_angle = M_PI, max_angle = -M_PI, tmp;
				for(int i = 0; i < n; i++) {
					Point v(vertex[i].x - p.x, vertex[i].y - p.y);
					tmp = v.get_angle();
					min_angle = std::min(min_angle, tmp);
					max_angle = std::max(max_angle, tmp);
				}
				return max_angle - min_angle;
			}
	} ;

}

# endif // GEOMETRY
