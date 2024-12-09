/*!
	\file
	\author Полина Клинова
	\brief Заголовочный файл с описанием и обработкой ошибок

	Файл содержит в себе класс Status, предназначенный для
	хранения ошибок и методов их обработки
*/

# ifndef STATUS
# define STATUS

/// Набор возможных ошибок
enum class err_type {
	success, ///< Ошибок не было
	open, ///< Не удалось открыть файл
	format, ///< Неправильный формат данных
	memory, ///< Не удалось выделить память
	unknown, ///< Неизвестная ошибка
} ;

/*!
	\brief Класс Status для обработки ошибок
*/
class Status {
	private:
		err_type state = err_type::success;
	public:
		/// Конструктор без аргументов
		Status () = default;
		/// Конструктор по единственному члену класса
		Status (const err_type& n_state) {
			state = n_state;
		}
		/// Сеттер для единственного члена класса
		void set_state (err_type n_state) {
			state = n_state;
		}
		/// Геттер для единственного члена класса
		err_type get_state () const {
			return state;
		}
		/// Проверка на succeess
		/// \return true при state == succces и false иначе
		bool good () const {
			return (state == err_type::success ? true : false);
		}
		/// Вывод соответствующих ошибкам сообщений о них
		void print_error_message (FILE *fp = stdout) const {
			if(state == err_type::success)
				return ;
			switch(state) {
				case err_type::open:
					fprintf(fp, "Error when opening file\n");
					break;
				case err_type::format:
					fprintf(fp, "Wrong data format\n");
					break;
				case err_type::memory:
					fprintf(fp, "Not enough memory\n");
					break;
				case err_type::unknown:
					fprintf(fp, "Unknown error\n");
					break;
			}
		}
		/// Оператор равенства
		/// \return true при равенстве state и false иначе
		bool operator== (const Status& n_st) {
			return (state == n_st.state ? true : false);
		}
		/// Оператор неравенства
		/// \return true при неравенстве state и false иначе
		bool operator!= (const Status& n_st) {
			return (state != n_st.state ? true : false);
		}
		/// Оператор присваивания
		Status& operator= (const Status& n_Status) {
			state = n_Status.state;
			return *this;
		}
} ;

# endif //STATUS
