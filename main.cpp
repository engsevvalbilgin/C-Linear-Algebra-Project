/*
 * @file Proje2
 * @description Program Matrix, Vektor, Complex ve Imaginary ve benzeri sınıflar üzerinde işlemler
 * // ve bu sınıflar arasındaki ilişkileri doğru şekilde kurmayı amaçlar.
 * @assignment 2.Ödev
 * @date 22.12.2023
 * @author Şevval Bilğin sevval.bilgin@stu.fsm.edu.tr
 */
#include <iostream>
#include <stdexcept>
using namespace std;
class LinearAlgebraObject
{
public:
    virtual void print() const = 0;
    

};
// İlk maddede söylenen:
// Imaginary adında, üye değişkeni private olan bir sınıf gerçeklenmiştir
// ve sayıların sanal kısmını ifade eder.
class Imaginary 
{
private:
    float imaginary_part;

public:
    Imaginary(int imag)
    {
        this->setImaginary_part(imag);
    }
    float const getImaginary_part() const
    {
        return this->imaginary_part;
    };
    void setImaginary_part(float nval)
    {
        this->imaginary_part = nval;
    }
    void print() const 
    {
        cout << this->getImaginary_part() << endl;
    }
};
// İkinci maddede söylenen:
// Complex adında, Imaginary'den türetilen ve üye değişkeni private olan bir sınıf gerçeklenmiştir.
// Sayıların  reel ve imaginer kısımlarını ifade der.
class Complex : public Imaginary
{
private:
    float re;

public:
    Complex() : Imaginary(0), re(0)
    {
    }
    Complex(float re_, float im_) : Imaginary(im_)
    {
        this->setReelPart(re_);
        this->setImaginary_part(im_);
    }

    void setReelPart(float nvalue)
    {
        this->re = nvalue;
    }
    float const getReel_part() const
    {
        return this->re;
    }
    void print() const 
    {
        cout << "Reel part:" << this->getReel_part() << endl;
        cout << "Imaginary part:" << this->getImaginary_part() << endl;
    }

    Complex operator=(Complex const &obj)
    {
        this->setReelPart(obj.getReel_part());
        this->setImaginary_part(obj.getImaginary_part());
        return *this;
    }
    Complex operator+(Complex const &obj) const
    {

        return Complex(obj.getReel_part() + this->getReel_part(), obj.getImaginary_part() + this->getImaginary_part());
    }
    Complex operator-(Complex const &obj) const
    {
        return Complex(this->getReel_part() - obj.getReel_part(), this->getImaginary_part() - obj.getImaginary_part());
    }
    Complex operator*(Complex const &obj)
    {
        Complex c(1, 1);
        c.setImaginary_part((this->getReel_part() * obj.getImaginary_part()) + (obj.getReel_part() * this->getImaginary_part()));
        c.setReelPart(obj.getReel_part() * this->getReel_part() - (this->getImaginary_part() * obj.getImaginary_part()));
        return c;
    }
    Complex operator~()
    {
        return Complex(this->getReel_part(), -this->getImaginary_part());
    }
    Complex operator/(Complex &obj)
    {

        Complex result(0, 1);
        if (!(obj.getImaginary_part() == 0 && obj.getReel_part() == 0))
        {

            Complex pay = (*this) * (~obj);
            Complex payda = obj * ~obj;

            if (!(payda.getReel_part() == 0 && payda.getImaginary_part() == 0))
            {
                float im = pay.getImaginary_part() * (1 / payda.getReel_part());
                float re = pay.getReel_part() * (1 / payda.getReel_part());
                pay.setImaginary_part(im);
                pay.setReelPart(re);
                result.setImaginary_part(pay.getImaginary_part());
                result.setReelPart(pay.getReel_part());
            }
            else
            {
                cout << "payda sifir oldu!!";
                throw runtime_error("payda sifir oldu!!");
            }
        }
        else
        {
            cout << "Sifira bolunemez!!" << endl;
            throw runtime_error("payda sifir oldu!!");
        }

        return result;
    }
    void operator+=(Complex const &obj)
    {
        this->setReelPart(this->getReel_part() + obj.getReel_part());
        this->setImaginary_part(this->getImaginary_part() + obj.getImaginary_part());
    }
    void operator-=(Complex const &obj)
    {
        this->setReelPart(this->getReel_part() - obj.getReel_part());
        this->setImaginary_part(this->getImaginary_part() - obj.getImaginary_part());
    }
    void operator*=(Complex const &obj)
    {
        float reel = (this->getReel_part() * obj.getReel_part()) - (this->getImaginary_part() * obj.getImaginary_part());
        float im = (this->getReel_part() * obj.getImaginary_part()) + (this->getImaginary_part() * obj.getReel_part());
        this->setReelPart(reel);
        this->setImaginary_part(im);
    }
    void operator/=(Complex &obj)
    {

        *this = *this / obj;
    }
    bool operator==(Complex const &obj)
    {
        if (this->getImaginary_part() == obj.getImaginary_part() && this->re == re)
        {
            return true;
        }
        return false;
    }
};
// Complex sayılar üzerinde tanımlı Matrix classı oluşturulmuştur.
class Matrix :public LinearAlgebraObject
{
private:
    size_t row, col;
    Complex **element;

public:
    Matrix() : row(0), col(0), element(nullptr) {}
    Matrix(size_t row, size_t col) : row(row), col(col) {}
    Matrix(const size_t row, const size_t col, Complex **element) : row(row), col(col)
    {
        this->element = new Complex *[row];
        for (size_t i = 0; i < row; ++i)
        {
            this->element[i] = new Complex[col];
            for (size_t j = 0; j < col; ++j)
            {

                this->element[i][j] = element[i][j];
            }
        }
    }
    Complex **getElements() const
    {
        return this->element;
    }
    size_t const getRowNumber() const
    {
        return row;
    }
    size_t const getColumnNumber() const
    {
        return col;
    }
    void set_rowNumber(size_t rows)
    {
        this->element = new Complex *[row];
        this->row = rows;
    }
    void set_colNumber(size_t cols)
    {
        for (size_t i = 0; i < this->getRowNumber(); i++)
        {
            this->element[i] = new Complex[col];
        }

        this->col = cols;
    }
    void setElements(Complex **elements, size_t row, size_t col)
    {
        for (size_t i = 0; i < this->row; ++i)
        {
            delete[] this->element[i];
        }
        delete[] this->element;

        this->element = new Complex *[row];
        for (int i = 0; i < row; i++)
        {

            this->element[i] = new Complex[col];
        }

        for (int i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {

                this->element[i][j].setReelPart(elements[i][j].getReel_part());
                this->element[i][j].setImaginary_part(elements[i][j].getImaginary_part());
            }
        }
    }
    void setElementAtWith(int row, int col, Complex newnum)
    {
        this->element[row][col].setReelPart(newnum.getReel_part());
        this->element[row][col].setImaginary_part(newnum.getImaginary_part());
    }

    Matrix transpose()
    {
        Matrix transposed(this->getRowNumber(), this->getColumnNumber(), this->getElements());
        for (size_t i = 0; i < this->getRowNumber(); i++)
        {
            for (size_t j = 0; j < this->getColumnNumber(); j++)
            {
                transposed.setElementAtWith(j, i, this->getElements()[i][j]);
            }
        }
        return transposed;
    }
    Complex determinant()
    {
        Complex determinant;
        if (this->getRowNumber() == this->getColumnNumber())
        {
            if (this->getRowNumber() == 2)
            {
                determinant = (this->getElements()[0][0] * this->getElements()[1][1]) - (this->getElements()[0][1] * this->getElements()[1][0]);
            }
            else if (this->getRowNumber() == 3)
            {
                determinant = (this->getElements()[0][0] * ((this->getElements()[1][1] * this->getElements()[2][2]) - (this->getElements()[2][1] * this->getElements()[1][2]))) - (this->getElements()[0][1] * ((this->getElements()[1][0] * this->getElements()[2][2]) - (this->getElements()[2][0] * this->getElements()[1][2]))) + (this->getElements()[0][2] * ((this->getElements()[1][0] * this->getElements()[2][1]) - (this->getElements()[2][0] * this->getElements()[1][1])));
            }
        }
        else
        {
            throw runtime_error("Kare olmayan matris uzerinde determinant hesaplanamaz!!");
        }
        return determinant;
    }
    void print() const 
    {

        for (size_t i = 0; i < row; i++)
        {

            for (size_t j = 0; j < col; j++)
            {
                cout << this->getElements()[i][j].getReel_part() << "+" << this->getElements()[i][j].getImaginary_part() << "i ";
            }
            cout << "\n";
        }
        cout << "---------------------\n";
    }

    Matrix operator=(Matrix const &obj)
    {
        size_t c = obj.getColumnNumber();
        size_t r = obj.getRowNumber();
        this->setElements(obj.getElements(), r, c);
        return *this;
    }
    Matrix operator+(Matrix const &obj) const
    {
        Matrix m(this->getRowNumber(), this->getColumnNumber(), this->getElements());
        if (this->getRowNumber() == obj.getRowNumber() && this->getColumnNumber() == obj.getColumnNumber())
        {

            for (int i = 0; i < this->getRowNumber(); i++)
            {
                for (int j = 0; j < this->getColumnNumber(); j++)
                {
                    Complex sum;
                    sum.setReelPart(this->getElements()[i][j].getReel_part() + obj.getElements()[i][j].getReel_part());

                    sum.setImaginary_part(this->getElements()[i][j].getImaginary_part() + obj.getElements()[i][j].getImaginary_part());

                    m.setElementAtWith(i, j, sum);
                }
            }
        }
        else
        {
            cout << "Hata: Matris boyutlari uyusmuyor!" << endl;
            throw std::runtime_error("Matris boyutlari uyuşmuyor!");
        }

        return m;
    }
    Matrix operator-(Matrix const &obj) const
    {
        Matrix m(this->getRowNumber(), this->getColumnNumber(), this->getElements());
        if (this->getRowNumber() == obj.getRowNumber() && this->getColumnNumber() == obj.getColumnNumber())
        {

            for (int i = 0; i < this->getRowNumber(); i++)
            {
                for (int j = 0; j < this->getColumnNumber(); j++)
                {
                    Complex sum = this->getElements()[i][j] - obj.getElements()[i][j];

                    m.setElementAtWith(i, j, sum);
                }
            }
        }
        else
        {
            cout << "Hata: Matris boyutlari uyusmuyor!" << endl;
            throw std::runtime_error("Matris boyutlari uyuşmuyor!");
        }

        return m;
    }
    Matrix operator*(Matrix const &obj)
    {
        Matrix product = Matrix(this->getRowNumber(), this->getColumnNumber());
        if (obj.getRowNumber() == this->getColumnNumber() && obj.getRowNumber() == obj.getColumnNumber())
        {

            product.set_rowNumber(this->getRowNumber());
            product.set_colNumber(obj.getColumnNumber());
            for (size_t i = 0; i < product.getRowNumber(); i++)
            {

                for (size_t j = 0; j < product.getColumnNumber(); j++)
                {

                    Complex sum(0, 0);

                    for (size_t k = 0; k < this->getColumnNumber(); k++)
                    {

                        sum = sum + (this->getElements()[i][k] * obj.getElements()[k][j]);
                    }

                    product.setElementAtWith(i, j, sum);
                }
            }
            return product;
        }
        else
        {
            throw std::runtime_error("Matris boyutlari uygun degil");
        }
    }
    void operator+=(Matrix const &obj)
    {

        *this = *this + obj;
    }
    void operator-=(Matrix const &obj)
    {
        *this = *this - obj;
    }
    void operator*=(Matrix const &obj)
    {
        *this = *this * obj;
    }
    bool operator==(Matrix const &obj)
    {
        if (!(this->getRowNumber() == obj.getRowNumber() && this->getColumnNumber() == obj.getColumnNumber()))
        {
            return false;
        }
        for (size_t i = 0; i < this->getRowNumber(); i++)
        {
            for (size_t j = 0; j < this->getColumnNumber(); j++)
            {
                if (!(this->getElements()[i][j] == obj.getElements()[i][j]))
                {
                    return false;
                }
            }
        }
        return true;
    }
};
class SquareMatrix : public Matrix
{
public:
    SquareMatrix(size_t size_, Complex **elements) : Matrix(size_, size_, elements)
    {
        this->setSize(size_);
        this->setElements(elements, size_, size_);
    }
    void setSize(size_t size)
    {
        Matrix::set_rowNumber(size);
        Matrix::set_colNumber(size);
    }
};
class IdentityMatrix : public Matrix
{
public:
    IdentityMatrix(size_t size_) : Matrix(size_, size_)
    {
        this->set_rowNumber(size_);
        this->set_colNumber(size_);
        Complex **elements = new Complex *[size_];
        for (size_t i = 0; i < size_; i++)
        {
            elements[i] = new Complex[size_];
        }
        for (size_t i = 0; i < size_; i++)
        {
            for (size_t j = 0; j < size_; j++)
            {
                if (i == j)
                {
                    this->setElementAtWith(i, j, Complex(1, 0));
                }
                else
                {

                    this->setElementAtWith(i, j, Complex(0, 0));
                }
            }
        }
    }
};
class TriangleMatrix : public Matrix
{ // elementler girilir ve
  // upper ya da lower triangle olacağına karar verilir
  // triangle_type 0'sa upper olur. Başka bir sayıysa lower olur.
public:
    TriangleMatrix(size_t row, size_t col, Complex **elements, int triangle_type = 0) : Matrix(row, col)
    {
        this->set_rowNumber(row);
        this->set_colNumber(col);

        this->setElements(elements, row, col);
        for (size_t i = 0; i < row; i++)
        {
            for (size_t j = 0; j < col; j++)
            {
                if (triangle_type == 0 && j < i)
                {
                    this->setElementAtWith(i, j, Complex(0, 0));
                }
                if (triangle_type != 0 && j > i)
                {
                    this->setElementAtWith(i, j, Complex(0, 0));
                }
            }
        }
    }
};

class Vector :public LinearAlgebraObject
{
private:
    size_t size;
    Complex *element;

public:
    Vector() : size(0), element(nullptr) {}
    Vector(size_t size_, Complex element)
    {
        this->setSize(1);
        this->getElement()[0].setReelPart(element.getReel_part());
        this->getElement()[0].setImaginary_part(element.getImaginary_part());
    }
    Vector(size_t size_, Complex *elements)
    {
        this->setSize(size_);
        this->setElement(elements);
    }
    Vector(size_t size_) : size(size_) {}
    size_t const getSize() const
    {
        return this->size;
    }
    Complex *getElement() const
    {
        return this->element;
    }
    void setSize(size_t size_)
    {
        this->size = size_;
        this->element = new Complex[size_];
    }
    void setElement(Complex *elements)
    {

        delete[] this->element;

        this->element = new Complex[size];

        for (int i = 0; i < size; i++)
        {

            this->element[i].setReelPart(elements[i].getReel_part());
            this->element[i].setImaginary_part(elements[i].getImaginary_part());
        }
    }
    void setElementAtWith(size_t size_, Complex newnum)
    {
        this->element[size_].setReelPart(newnum.getReel_part());
        this->element[size_].setImaginary_part(newnum.getImaginary_part());
    }
    void print() const 
    {
        for (size_t i = 0; i < this->getSize(); i++)
        {
            cout << this->getElement()[i].getReel_part() << "+" << this->getElement()[i].getImaginary_part() << "i ";
        }
        cout << "\n------------------------" << endl;
    }
    Vector operator=(Vector const &obj)
    {

        this->setSize(obj.getSize());
        this->setElement(obj.getElement());
        return *this;
    }
    Vector operator+(Vector const &obj)
    {
        Vector sum;
        if (this->getSize() == obj.getSize())
        {
            sum.setSize(this->getSize());
            for (size_t i = 0; i < sum.getSize(); i++)
            {
                sum.setElementAtWith(i, this->getElement()[i] + obj.getElement()[i]);
            }
        }
        else
        {
            cout << "Hata: Matris boyutlari uyusmuyor!" << endl;
            throw std::runtime_error("Matris boyutlari uyuşmuyor!");
        }

        return sum;
    }
    Vector operator-(Vector const &obj)
    {
        Vector n;
        if (this->getSize() == obj.getSize())
        {
            n.setSize(this->getSize());
            for (size_t i = 0; i < n.getSize(); i++)
            {
                n.setElementAtWith(i, this->getElement()[i] - obj.getElement()[i]);
            }
        }
        else
        {
            cout << "Hata: Vektor boyutlari uyusmuyor!" << endl;
            throw std::runtime_error("Vektor boyutlari uyuşmuyor!");
        }
        return n;
    }
    Vector operator*(Vector const &obj)
    {

        Complex complex_product;
        if (this->getSize() == obj.getSize())
        {
            for (size_t i = 0; i < this->getSize(); i++)
            {
                complex_product = complex_product + this->getElement()[i] * obj.getElement()[i];
            }
        }
        else
        {
            cout << "Hata: Vektor boyutlari uyusmuyor!" << endl;
            throw std::runtime_error("Vektor boyutlari uyuşmuyor!");
        }
        Complex *c;
        c[0] = complex_product;
        Vector product = Vector(1, complex_product);

        return product;
    }
    void operator*=(Vector &obj)
    {
        Vector a = *this * obj;
        this->setSize(1);
        this->setElement(a.getElement());
    }
    void operator+=(Vector &obj)
    {

        *this = *this + obj;
    }
    void operator-=(Vector &obj)
    {
        *this = *this - obj;
    }
    bool operator==(Vector &obj)
    {
        if (obj.getSize() == this->getSize())
        {
            for (size_t i = 0; i < this->getSize(); i++)
            {
                if (!(this->getElement()[i] == obj.getElement()[i]))
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
        return true;
    }
};
int main()
{

    // Complex sınıfı için atama operatörü override edilmiştir.
      /*
      Complex c1 = Complex(5, 2);
      Complex c2 = Complex(5, -3);
      Complex c=c1;
      c.print();
      */
    // Complex sınıfı için toplama operatörü override edilmiştir.
    /* Complex c1 = Complex(5, 2);
     Complex c2 = Complex(5, -3);
     Complex c=c1+c2;
     c.print();*/
    // Complex sınıfı için çıkarma operatörü override edilmiştir.
    /*Complex c1 = Complex(5, 2);
    Complex c2 = Complex(5, 3);
    Complex c = c1 - c2;
    c.print();*/
    // Complex sınıfı için çarpma operatörü override edilmiştir.
    //(5+2i)*(5+2i)=21+20i olmalı
    /*
     Complex c1 = Complex(5, 2);
     Complex c2 = Complex(5, 2);
     Complex c = c1 * c2;
     c.print();
     */
    // Complex sınıfı için eşlenik operatörü override edilmiştir.
    //~(5+2i)=5-2i olmalı
    /*
     Complex c1 = Complex(5, 2);
     Complex c = ~c1;
     c.print();
     */
    // Complex sınıfı için bölme operatörü override edilmiştir.
    //(5+2i)/(5-2i)=21/29 +20/29i=0.74241+ 0.6896i yapar
    /*
     Complex c1 = Complex(5, 2);
     Complex c2 = Complex(5, -2);
     c1.print();
     c2.print();
     Complex c = c1 /c2;
     cout<<"bolme sonucu:\n";
     c.print();
*/
 
    // Complex sınıfı için toplama atama operatörü override edilmiştir.
    /*
     Complex c1 = Complex(4, 2);
     Complex c2 = Complex(5, 3);
     c1+= c2;
     c1.print();
     */
    // Complex sınıfı için çıkarma atama operatörü override edilmiştir.
    /*
     Complex c1 = Complex(4, 2);
     Complex c2 = Complex(5, 3);
     c1-= c2;
     c1.print();
     */
    // Complex sınıfı için çarpma atama operatörü override edilmiştir.
    // sonucun reel kısım 14, imaginer kısım 22 olmalıdır
    /*
    Complex c1 = Complex(4, 2);
     Complex c2 = Complex(5, 3);
     c1*= c2;
     c1.print();
     */
    // Complex sınıfı için bölme atama operatörü override edilmiştir.
    //  sonucun reel kısım 0.88, imaginer kısım -0.16 olmalıdır
    /*
     Complex c1 = Complex(4, 2);
     Complex c2 = Complex(4, 3);
     c1/= c2;
     c1.print();
     */
    // Complex sınıfı için eşit mi operatörü override edilmiştir.
    /*
    Complex c1 = Complex(4, 2);
    Complex c2 = Complex(4, 3);
    Complex c3 = Complex(4, 2);
    bool isEq = c1 == c2;
    bool isEq2 = c1 == c3;
    if (isEq)
    {
        cout << "c1 ve c2 ayni sayilardir" << endl;
    }
    else
    {
        cout << "c1 ve c2 ayni sayilar degillerdir" << endl;
    }
    if (isEq2)
    {
        cout << "c1 ve c3 ayni sayilardir" << endl;
    }
    else
    {
        cout << "c1 ve c3 ayni sayilar degillerdir" << endl;
    }*/
    //İLERİDEKİ ÖRNEKLER İÇİN GEREKLİ MATRİS VE COMPLEX SAYILAR
    /*Complex c1 = Complex(1, 1);
    Complex c2 = Complex(1, 1);
    Complex c3 = Complex(1, 1);
    Complex c4 = Complex(1, 1);
    size_t m1_rownum = 2;
    size_t m1_colnum = 2;

    Complex **m1 = new Complex *[m1_rownum];
    for (int i = 0; i < m1_rownum; ++i)
    {
        m1[i] = new Complex[m1_colnum];
    }
    m1[0][0] = c1;
    m1[0][1] = c2;
    m1[1][0] = c3;
    m1[1][1] = c4;

    Complex c5 = Complex(1, 3);
    Complex c6 = Complex(3, 1);
    Complex c7 = Complex(1, 1);
    Complex c8 = Complex(1, 1);
    size_t m2_rownum = 2;
    size_t m2_colnum = 2;
    Complex **m2 = new Complex *[m2_rownum];
    for (int i = 0; i < m2_rownum; ++i)
    {
        m2[i] = new Complex[m2_colnum];
    }
    m2[0][0] = c5;
    m2[0][1] = c6;
    m2[1][0] = c7;
    m2[1][1] = c8;
    Matrix first_matrix = Matrix(m1_rownum, m1_colnum, m1);
    Matrix sec_matrix = Matrix(m2_rownum, m2_colnum, m2);
    size_t m3_rownum = 3;
    size_t m3_colnum = 3;
    Complex **m3 = new Complex *[m3_rownum];
    for (int i = 0; i < m3_rownum; ++i)
    {
        m3[i] = new Complex[m3_rownum];
    }
    m3[0][0] = c1;
    m3[0][1] = c2;
    m3[0][2] = c3;
    m3[1][0] = c4;
    m3[1][1] = c5;
    m3[1][2] = c6;
    m3[2][0] = c7;
    m3[2][1] = c8;
    Complex c9 = Complex(8, 1);
    m3[2][2] = c9;
    Matrix third_matrix = Matrix(m3_rownum, m3_colnum, m3);*/
    // first_matrix.print();
    // sec_matrix.print();
    // third_matrix.print();

    //  matrix toplama işlemi ve + operatörü override işlemi test edilmiştir.
    /* Matrix n = first_matrix + sec_matrix;
     n.print();
    */
    // matrix çıkarma işlemi - operatörü override işlemi test edilmiştir.
    /*
      Matrix n = first_matrix -sec_matrix;
      n.print();
    */

    // matrix çarpma işlemi * operatörü override işlemi test edilmiştir.
    // sonuç -2+6i 2+6i olmalı
    //       -2+6i 2+6i
    /*Matrix n = first_matrix * sec_matrix;
    n.print();
    */

    // matrix atama işlemi = operatörü override işlemi test edilmiştir.
     /*sec_matrix=first_matrix;
     sec_matrix.print();*/
    // matrix atama toplama işlemi ve += operatörü override işlemi test edilmiştir.
    /* first_matrix += sec_matrix;
     first_matrix.print();
     */
    // matrix atama çıkarma işlemi ve -= operatörü override işlemi test edilmiştir.
    /*
     first_matrix -= sec_matrix;
     first_matrix.print();
     */
    // matrix atama çarpma işlemi ve *= operatörü override işlemi test edilmiştir.
 /*
    first_matrix *= sec_matrix;
    first_matrix.print();
  */  
    // matrix eşitlik işlemi ve == operatörü override işlemi test edilmiştir.
    /*
    bool a= first_matrix==sec_matrix;
    //first_matrix=sec_matrix;
     //a= first_matrix==sec_matrix;
    if(a){cout<<"true";}
    else{cout<<"false";}
    */
    // matrisin transpozunu hesaplama işlemi test edilmişir.
    /* Matrix tr=third_matrix.transpose();
     tr.print();*/
    // matrisin determinantını hesaplama işlemi test edilmişir.
    // 1+3i 3+1i
    // 1+1i 1+1i
    // ikinci matrisin determinant -4 çıkmalı,üçüncü -14+14i çıkmalı
    /*Complex a = sec_matrix.determinant();
    Complex b = third_matrix.determinant();
    cout << "2. matrisin determinanti: " << a.getReel_part() << "+" << a.getImaginary_part() << "i" << endl;
    cout << "3. matrisin determinanti: " << b.getReel_part() << "+" << b.getImaginary_part() << "i";
*/
    // verilen sayi boyutlarında kare identity matris oluşturma işlemi test edilmiştir.
    /*IdentityMatrix a = IdentityMatrix(4);
    a.print();*/
    /* c5 = (1, 3);
   c6 = (3, 1);
   c7 = Complex(1, 1);
   c8 = Complex(1, 1);*/

    // verilen sayi boyutlarında square matris oluşturma işlemi test edilmiştir.
    /*
    SquareMatrix s = SquareMatrix(2, m2);
    s.print();
    */
    // girilen Complex türünden iki boyutlu pointerı upper ya da lower trianmgle matris yapar
    /* Matrix m = Matrix(3, 3, m3);
     m.print();
     // upper
     TriangleMatrix t1 = TriangleMatrix(3, 3, m3, 0);
     // lower
     TriangleMatrix t2 = TriangleMatrix(3, 3, m3, 1);
     t1.print();
     t2.print();*/
    // VEKTÖRLER
    /*Complex *list1 = new Complex[2];
    Complex *list2 = new Complex[2];
    list1[0] = c1;
    list1[1] = c2;
    list2[0] = c5;
    list2[1] = c5;
    Vector v1 = Vector(2, list1);
    Vector v2 = Vector(2, list2);
     v1.print();
     v2.print();*/
    //  vektör toplama işlemi ve + operatörü override işlemi test edilmiştir.
    /*Vector v3 = v1 + v2;
    v3.print();*/
    // vektör çıkarma işlemi ve - operatörü override işlemi test edilmiştir.
    /* Vector v3 = v1 - v2;
     v3.print();*/
    // vektör çarpma işlemi ve * operatörü override işlemi test edilmiştir.(-4+8i çıkmalı)
    /* Vector v3 = v1 * v2;
     v3.print();*/
    // vektör atama işlemi ve = operatörü override işlemi test edilmiştir.
    /*Vector v3 = v2;
    v3.print();*/
    // vektör toplama atama işlemi ve += operatörü override işlemi test edilmiştir.
    /* Vector v3=v1;;
     v3.print();
     v3 += v1;
     v3.print();*/
    // vektör çıkarma atama işlemi ve -= operatörü override işlemi test edilmiştir.
   /* Vector v3 = v1 + v2;
    v3.print();
    v3-=v1;
    v3.print();*/
    // vektör çarpma atama işlemi ve *= operatörü override işlemi test edilmiştir.(-4+8i çıkmalı)
    /* Vector v3 = v1 ;
     v3.print();
     v3 *= v2;
     v3.print();*/
    // vektör eşit eşittir işlemi ve == operatörü override işlemi test edilmiştir.
    /*,Vector v3 = v1;
    if(v3==v1){
        cout<<"v1 and v3 are equal"<<endl;
    }*/

    return 0;
}
