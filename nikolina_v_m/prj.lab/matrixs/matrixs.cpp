#include <matrixs/matrixs.hpp>

#include <iostream>
#include <algorithm>

using SizeType = std::tuple<std::ptrdiff_t, std::ptrdiff_t>;

MatrixS::MatrixS(const SizeType& size) {
	if (std::get<0>(size) < 0 || std::get<1>(size) < 0) {
		throw std::invalid_argument("Size can't be less than 0");
	}
	else
	{
		size_ = std::make_tuple(std::get<0>(size), std::get<1>(size));
		row_capacity_ = std::get<0>(size);
		col_capacity_ = std::get<1>(size);
		if (std::get<0>(size_) == 0 || std::get<1>(size_) == 0) {
			data_ = nullptr;
		}
		else {
			data_ = new int[col_capacity_ * row_capacity_];
			std::fill(data_, data_ + col_capacity_ * row_capacity_, 0);
		}
	}
}
MatrixS::MatrixS(const std::ptrdiff_t m, const std::ptrdiff_t n) {
	if (m < 0 || n < 0) {
		throw std::invalid_argument("Size can't be less than 0");
	}
	else
	{
		size_ = std::make_tuple(m, n);
		row_capacity_ = std::get<0>(size_);
		col_capacity_ = std::get<1>(size_);
		if (std::get<0>(size_) == 0 || std::get<1>(size_) == 0) {
			data_ = nullptr;
		}
		else {
			data_ = new int[col_capacity_ * row_capacity_];
			std::fill(data_, data_ + col_capacity_ * row_capacity_, 0);
		}
	}
}
MatrixS::~MatrixS() {
	if (data_) {
		delete[] data_;
		data_ = nullptr;
	}
}

MatrixS::MatrixS(const MatrixS& other) {
	size_ = other.size_;
	col_capacity_ = other.col_capacity_;
	row_capacity_ = other.row_capacity_;
	if (other.data_) {
		data_ = new int[col_capacity_ * row_capacity_];
		std::copy(other.data_, other.data_ + other.col_capacity_ * other.row_capacity_, data_);
	}
	else {
		data_ = nullptr;
	}
}
MatrixS& MatrixS::operator=(const MatrixS& other) {
	if (data_ != other.data_)
	{
		size_ = other.size_;
		col_capacity_ = other.col_capacity_;
		row_capacity_ = other.row_capacity_;
		if (other.data_) {
			data_ = new int[col_capacity_ * row_capacity_];
			std::copy(other.data_, other.data_ + other.col_capacity_ * other.row_capacity_, data_);
		}
		else {
			data_ = nullptr;
		}
	}
	return *this;
}

int& MatrixS::at(const SizeType& elem) {
	if (std::get<0>(elem) < 0 || std::get<0>(elem) >= std::get<0>(size_) || std::get<1>(elem) < 0 || std::get<1>(elem) >= std::get<1>(size_)) {
		throw std::out_of_range("index out of range");
	}
	else
	{
		return (data_[std::get<0>(elem) * col_capacity_ + get<1>(elem)]);
	}
}
const int& MatrixS::at(const SizeType& elem) const {
	if (std::get<0>(elem) < 0 || std::get<0>(elem) >= std::get<0>(size_) || std::get<1>(elem) < 0 || std::get<1>(elem) >= std::get<1>(size_)) {
		throw std::out_of_range("index out of range");
	}
	else
	{
		return (data_[std::get<0>(elem) * col_capacity_ + get<1>(elem)]);
	}
}
int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) {
	if (i < 0 || i >= std::get<0>(size_) || j < 0 || j >= std::get<1>(size_)) {
		throw std::out_of_range("index out of range");
	}
	else
	{
		return (data_[i * col_capacity_ + j]);
	}
}
const int& MatrixS::at(const std::ptrdiff_t i, const std::ptrdiff_t j) const {
	if (i < 0 || i >= std::get<0>(size_) || j < 0 || j >= std::get<1>(size_)) {
		throw std::out_of_range("index out of range");
	}
	else
	{
		return (data_[i * col_capacity_ + j]);
	}
}

void MatrixS::resize(const SizeType& new_size) {
	if (std::get<0>(new_size) <= 0 || std::get<1>(new_size) <= 0) {
		throw std::invalid_argument("Size can't be less than 0");
	}
	else
	{
		const ptrdiff_t& new_row = std::get<0>(new_size);
		const ptrdiff_t& new_col = std::get<1>(new_size);
		if (new_row <= row_capacity_ && new_col <= col_capacity_) {
			size_ = std::make_tuple(new_row, new_col);
		}
		else {
			ptrdiff_t new_row_capacity = std::max(row_capacity_ * 2, new_row);
			ptrdiff_t new_col_capacity = std::max(col_capacity_ * 2, new_col);
			int* new_data = new int[new_col_capacity * new_row_capacity];
			std::fill(new_data, new_data + new_col_capacity * new_row_capacity, 0);
			for (ptrdiff_t i = 0; i < std::get<0>(size_); ++i) {
				for (ptrdiff_t j = 0; j < std::get<1>(size_); ++j) {
					new_data[i * new_col_capacity + j] = data_[i * col_capacity_ + j];
				}
			}
			delete[] data_;
			data_ = new_data;
			size_ = std::make_tuple(new_row, new_col);
			row_capacity_ = new_row_capacity;
			col_capacity_ = new_col_capacity;
		}
	}
}
void MatrixS::resize(const std::ptrdiff_t i, const std::ptrdiff_t j) {
	if (i <= 0 || j <= 0) {
		throw std::invalid_argument("Size can't be less than 0");
	}
	else
	{
		const ptrdiff_t& new_row = i;
		const ptrdiff_t& new_col = j;
		if (new_row <= row_capacity_ && new_col <= col_capacity_) {
			size_ = std::make_tuple(new_row, new_col);
		}
		else {
			ptrdiff_t new_row_capacity = std::max(row_capacity_ * 2, new_row);
			ptrdiff_t new_col_capacity = std::max(col_capacity_ * 2, new_col);
			int* new_data = new int[new_col_capacity * new_row_capacity];
			std::fill(new_data, new_data + new_col_capacity * new_row_capacity, 0);
			for (ptrdiff_t i = 0; i < std::get<0>(size_) && i < new_row_capacity; ++i) {
				for (ptrdiff_t j = 0; j < std::get<1>(size_) && j < new_col_capacity; ++j) {
					new_data[i * new_col_capacity + j] = data_[i * col_capacity_ + j];
				}
			}
			delete[] data_;
			data_ = new_data;
			size_ = std::make_tuple(new_row, new_col);
			row_capacity_ = new_row_capacity;
			col_capacity_ = new_col_capacity;
		}
	}
}

const SizeType& MatrixS::ssize() const noexcept {
	return size_;
}

std::ptrdiff_t MatrixS::nRows() const noexcept {
	return std::get<0>(size_);
}

std::ptrdiff_t MatrixS::nCols() const noexcept {
	return std::get<1>(size_);
}

