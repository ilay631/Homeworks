#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
using namespace std;


class Transport {
public:
	virtual void info() = 0;
	int speed;
};


class Car : public Transport
{
private:
	string name;
public:
	Car(int speed) { this->speed = speed; }
	Car(int speed, string name) { this->speed = speed; this->name = name; }
	~Car() {};
	string getName() { return name; }
	void setName(string name) { this->name = name; }

	void increaseSpeed(int value) {
		this->speed += value;
	}
	void decreaseSpeed(int value) {
		this->speed -= value;
	}
	int getSpeed() {
		return this->speed;
	}
	virtual void info() {
		cout << "Машина " << this->getName() << " со скоростью " << this->getSpeed() << endl;
	}
};


class Ship : public Transport {
private:
	string name;
public:
	Ship(int speed) { this->speed = speed; }
	Ship(int speed, string name) { this->speed = speed; this->name = name; }
	~Ship() {};
	void info() {
		cout << "Корабль " << this->name << " со скоростью " << this->speed << endl;
	}
};


class Cabriolet :public Car
{
public:
	Cabriolet(int speed) : Car(speed) {}
	Cabriolet(int speed, string name) : Car(speed, name) {}
	~Cabriolet() {};
	void info() {
		cout << "Кабриолет " << this->getName() << " со скоростью " << this->getSpeed() << endl;
	}
};


class Kolimaga :public Car
{
public:
	Kolimaga(int speed) : Car(speed) {}
	Kolimaga(int speed, string name) : Car(speed, name) {}
	~Kolimaga() {};
	void info() {
		cout << "Колымага " << this->getName() << " со скоростью " << this->getSpeed() << endl;
	}
};


class CarFactory {
public:
	virtual Car* createCar(int speed) {
		return new Car(speed);
	}
	virtual Car* createCar(int speed, string name) {
		return new Car(speed, name);
	}
	virtual ~CarFactory() {};
};


class CabrioletFactory : public CarFactory {
public:
	Car* createCar(int speed) {
		return new Cabriolet(speed);
	}
	Car* createCar(int speed, string name) {
		return new Cabriolet(speed, name);
	}
};


class KolimagaFactory : public CarFactory {
public:
	Car* createCar(int speed) {
		return new Kolimaga(speed);
	}

	Car* createCar(int speed, string name) {
		return new Kolimaga(speed, name);
	}
};


class ShipFactory {
public: 
	Ship* createShip(int speed, string name) {
		return new Ship(speed, name);
	}
	~ShipFactory() {}
};


void refuel(Transport* transport) {
	cout << "Запривили топливом" << endl;

	Ship* ship = dynamic_cast<Ship*>(transport);
	if (ship) {
		cout << "Установили GPS" << endl;
		return;
	}

	Car* car = dynamic_cast<Car*>(transport);
	if (car) {
		cout << "Поменяли колеса" << endl;
		return;
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	vector<Transport*> carsAndShips;
	ShipFactory shipFactory;
	KolimagaFactory kolimagaFactory;
	CabrioletFactory cabrioletFactory;
	CarFactory carFactory;

	for (int i = 0; i < 5; i++) {
		cout << "Выберите тип транспорта (1 - Корабль, 2 - Машина, 3 - Кабриолет, 4 - Колымага)." << endl;
		int type;
		cin >> type;
		cout << "Введите название и скорость данного транспорта" << endl;
		int speed;
		string name;
		cin >> name >> speed;
		switch (type)
		{
		case 1:
			carsAndShips.push_back(shipFactory.createShip(speed, name));
			break;

		case 2:
			carsAndShips.push_back(carFactory.createCar(speed, name));
			break;

		case 3:
			carsAndShips.push_back(cabrioletFactory.createCar(speed, name));
			break;

		case 4:
			carsAndShips.push_back(kolimagaFactory.createCar(speed, name));
			break;

		default:
			cout << "Такого типа транспортного средства нет" << endl;
			return -1;
			break;
		}

	}
	
	for (int i = 0; i < carsAndShips.size(); i++) {
		for (int j = 0; j < carsAndShips.size() - i - 1; j++) {
			if (carsAndShips[j]->speed < carsAndShips[j + 1]->speed)
				swap(carsAndShips[j], carsAndShips[j + 1]);
		}
	}

	for (int i = 0; i < 5; i++) {
		carsAndShips[i]->info();
		refuel(carsAndShips[i]);
		cout << endl;
	}
	

	return 0;
}
