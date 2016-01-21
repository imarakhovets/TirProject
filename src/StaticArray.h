#pragma once

#ifndef __STATICARRAY_H__
#define __STATICARRAY_H__



/// Шаблон одномерного массива - аналога статического массива Си.
/// Обеспечивает:
/// 1. Зануление элементов при создании (в отличие от классического массива).
/// 2. Контроль диапазонов при индексировании (в отличие от массивов и std::vector).
/// 3. Отображение содержимого в отладчике Visual Studio (в отличие от std::vector).
/// 4. Выдачу в size() числа со знаком, так что для прохода по массиву
/// можно использовать тип int без предупреждений компилятора (в отличие от std::vector).
///
/// Использование:
/// Вместо
/// int a[10];
///
/// нужно переменную объявлять как
/// StaticArray<int, 10> a;
///
/// вот и все различия.
template<typename T, int SIZE>
class StaticArray {
private:

	/// Массив, обёрнутый в этот класс.
	T _data[SIZE];

public:

	/// Конструктор - зануление элементов массива.
	StaticArray() {
		for (int i = 0; i < SIZE; i++) {
			_data[i] = T();
		}
	}

	/// Конструктор - задание одинаковых значений элементов массива.
	explicit StaticArray(T value) {
		for (int i = 0; i < SIZE; i++) {
			_data[i] = value;
		}
	}

	/// Оператор индексирования массива с проверкой диапазона.
	T & operator [] (int pos) {
		Assert(0 <= pos && pos < SIZE);
#ifdef ENGINE_TARGET_WINDOWS_METRO
		if (0 <= pos && pos < SIZE) {
			return _data[pos];
		}
		return _data[0];
#else
		return _data[pos];
#endif
	}

	/// Оператор индексирования константного массива.
	const T & operator [] (int pos) const {
#ifdef ENGINE_TARGET_WINDOWS_METRO
		Assert(0 <= pos && pos < SIZE);
		if (0 <= pos && pos < SIZE) {
			return _data[pos];
		}
		return _data[0];
#else
		return _data[pos];
#endif
	}

	/// Функция получения размера массива в элементах.
	/// Не слишком актуальна, поскольку размер массива
	/// всегда известен в момент использования,
	/// поскольку следует из типа массива.
	int size() const {
		return SIZE;
	}
};


#endif // __STATICARRAY_H__
