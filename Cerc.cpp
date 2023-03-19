#include<iostream>


class Punct
{
private: 
	float x, y;

public:
	Punct() {};

	Punct(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void setX(float x)
	{
		this->x = x; //this este un pointer, este plasat ca param in orice metoda din clasa 
	}
	void setY(float y)
	{
		this->y = y;
	}
	float getX()
	{
		return x;
	}
	float getY()
	{
		return y;
	}

	float distantaLa(Punct p)
	{
		return sqrt((x - p.x) * (x - p.x)) + (y - p.y) * (y - p.y);
	}
		

};

//supraincarcare << si >>

std::ostream& operator << (std::ostream& os, Punct p)
{
	os << "(" << p.getX() << "," << p.getY() << ")"; 
	return os; 
}

std::istream& operator >> (std::istream& is, Punct& p)
{
	float x, y;
	is >> x >> y;
	p.setX(x);
	p.setY(y);

	return is;
}



class Cerc
{
private:
	Punct centru;
	float raza;

public:

	//constructorii nu se bat cap in cap cu metodele de initializare

	Cerc()
	{}

	Cerc(Punct c, float raza)
	{
		centru = c;
		this->raza = raza;
	}

	Cerc(float x, float y, float raza)
	{
		centru = Punct(x, y);
		this->raza = raza;


		/*centru.setX(x); 
		centru.setY(y);
		this->raza = raza;*/
	}



	void initializare(float x, float y, float raza)
	{
		this->centru.setX(x); //sau putem scrie fara this centru.setX(x)
		centru.setY(y);
		this->raza = raza; 
	}

	void initializare(Punct c, float raza)
	{
		centru = c;
		this->raza = raza;

	}

	void afisare()
	{
		std::cout << "((" << centru.getX() << "," << centru.getY() << ")," << raza << ")";
	}

	bool esteUnCerc(Punct p)
	{
		return (raza > p.distantaLa(centru));
		
	}

	float operator !() // implicit vine obiectul curent, deci nu punem parametrii (supraincarcare de operatori)
	{
		return raza * raza * 3.14;
	}

	Punct getCentru()
	{
		return centru; 
	}

	float getRaza()
	{
		return raza;
	}

	//operator + pentru 2 obiecte de tip cerc construieste un nou obiect cu raza egala 
	//cu suma razelor si centru la mijlocul distantei dintre cele doua centre

	Cerc operator +(Cerc c)
	{
		Punct centruNou((centru.getX() + c.centru.getX()) / 2, ((centru.getY() + c.centru.getY()) / 2));
		return Cerc(centruNou, raza + c.raza);
	}

	friend std::istream& operator >> (std::istream& is, Cerc c)
	{
		is >> c.centru >> c.raza;
		return is; 
	}

};

std::ostream& operator << (std::ostream& os, Cerc c)
{
	os << "(" << c.getCentru() << "," << c.getRaza() << ")\n"; 
	return os;
 }




int main()
{
	Cerc c;
	std::cin >> c;  // supraincarcare operator 

	//Cerc c (0,0,5); //folosim constructor

	std::cout << c; //supraincarcare de operatori 

	c.initializare(0, 0, 5);
	/*c.afisare();*/

	//Punct p1(2, 3);

	Punct p1;
	std::cin >> p1; // merge 


	//std::cout << p1 << "\n"; //supraincarcare << - deci nu va merge 


	//if (c.esteUnCerc(p1))
	//	std::cout << "p1 este un cerc";

	//std::cout <<"Aria cercurlui:" << !c; // supraincarcare de operatori


	Cerc c1(p1, 4);

	Punct p;  //avem deja constructor definit de noi in clasa, deci nu se mai apeleaza cel default (cel default se foloseste cand nu avem definit altul)
	p.setX(8);   
	p.setY(-4);

	c.initializare(p, 5);

	//c.afisare();

	//c1.afisare();

	//Punct p; - de verificat!!!

	(c1 + c).afisare();  

	

}