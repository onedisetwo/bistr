/*!
	\file
	\author Полина Клинова
	\brief Файл исходного кода программы решения задачи 1

	Содержит main, а также класс Result и функцию process для обработки ответов на задачу
*/

# include <stdio.h>
# include <string.h>

# include "../inc/geometry.h"
# include "../inc/status.h"

/*!
	\brief Класс для обработки результата тестирования

	Содержит поля: status - код ошибки, и answer - ответ при успешном выполнении
*/
class Result {
	private:
		Status status = Status(err_type::unknown); ///< Тип ошибки при исполнении
		double answer = 0; ///< Ответ на задачу
	public:
		/// Конструктор согласно значниям по умолчанию
		Result () = default;
		/// Конструтор по status
		/// \defails поле answer не изменяется, используется в случае ошибки при исполнении
		Result (Status n_status) {
			status = n_status;
		}
		/// Конструктор по answer, status считаетяс успешным
		Result (double n_answer) {
			status.set_state(err_type::success);
			answer = n_answer;
		}
		/// Конструктор по всем полям
		Result (Status n_status, double n_answer) {
			status = n_status;
			answer = n_answer;
		}
		/*
			Печатает результат работы задачи

			\param spaces Количество пробелов перед выводом (0)
			\param fp Файл вывода (stdout)

			Печатает на двух строках либо [OK], [Answer]; либо [FAIL], [Error message]
		*/
		void print (int spaces = 0, FILE *fp = stdout) const {
			for(int i = 0; i < spaces; i++)
				fprintf(fp, " ");
			if(status.good()) {
				fprintf(fp, "[OK]\n");
				for(int i = 0; i < spaces; i++)
					fprintf(fp, " ");
				fprintf(fp, "Answer: %lf\n", answer);
			}
			else{
				fprintf(fp, "[FAIL]\n");
				for(int i = 0; i < spaces; i++)
					fprintf(fp, " ");
				status.print_error_message(fp);
			}
		}
} ;

/*!
	Запускает решение задачи 1 на данном файле

	\param filename Имя файла с исходными данными
	\return Result - код ошибки и (если success) ответ
*/
Result process (const char* filename) {
	int n;
	R2::Polygon m_polygon;
	R2::Point viewpoint;
	FILE *fp;
	Status tmp_status;
	if(!(fp = fopen(filename, "r")))
		return Result(err_type::open);
	if(!(tmp_status = m_polygon.read(fp, false)).good() ||
		!(tmp_status = viewpoint.read(fp, false)).good()){
		fclose(fp);
		return Result(tmp_status);
	}
	return Result(m_polygon.get_view_angle(viewpoint));
}

/*!
	Функция main

	Имеет 2 варианта, выбираемых при компиляции:
	автоматизированного и ручного тестирования
*/
int main (void) {
#ifdef SELFTEST
	const int TEST_NUM = 4; ///< Количество тестов
	const char* test_filenames[TEST_NUM] = {"non-existent.txt", "empty.txt",
		"wrong1.txt", "test1.txt"}; ///< Имена тестовых файлов
	for(int i = 0; i < TEST_NUM; i++) {
		char folder[30] = "test/";
		char* final_filename = strcat(folder, test_filenames[i]);
		Result curr_result;
		printf("%s \n", test_filenames[i]);
		curr_result = process(final_filename);
		curr_result.print(2);
	}
# else
	char* filename;
	Result curr_result;
	scanf("%s", filename);
	printf("%s \n", filename);
	curr_result = process(filename);
	curr_result.print(2);
# endif
	return 0;
}
