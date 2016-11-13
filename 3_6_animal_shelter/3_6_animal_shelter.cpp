// Animal Shelter: An animal shelter, which holds only dogs and cats, operates
// on a strictly "first in, first out" basis. People must adopt either the
// "oldest" (based on arrival time) of all animals at the shelter, or they can
// select whether they would prefer a dog or a cat (and will receive the oldest
// animal of that type). They cannot select which specific animal they would
// like. Create the data structures to maintain this system and implement
// operations such as enqueue, dequeueAny, dequeueDog and dequeueCat. You may
// use the built-in LinkedList data structure.

#include <queue>
#include "gtest/gtest.h"

class Animal {
public:
  Animal(const std::string &name) : name_(name), id_(-1) {}
  virtual ~Animal() {}

  std::string name() const {
    return name_;
  }

  int id() const {
    return id_;
  }

  void id(int id) {
    id_ = id;
  }

protected:
  std::string name_;
  int id_;
};

class Cat : public Animal {
public:
  Cat(const std::string &name) : Animal(name) {}
  virtual ~Cat() {}
};

class Dog : public Animal {
public:
  Dog(const std::string &name) : Animal(name) {}
  virtual ~Dog() {}
};

class AnimalShelter {
public:
  void Enqueue(Animal &animal) {
    if (auto *c = dynamic_cast<Cat*>(&animal)) {
      animal.id(id_);
      id_++;
      cats_.push(*c);
    } else if (auto *d = dynamic_cast<Dog*>(&animal)) {
      animal.id(id_);
      id_++;
      dogs_.push(*d);
    }
  }

  Cat DequeueCat() {
    const auto cat = cats_.front();
    cats_.pop();
    return cat;
  }

  Dog DequeueDog() {
    const auto dog = dogs_.front();
    dogs_.pop();
    return dog;
  }

  Animal DequeueAny() {
    if (cats_.empty()) {
      return DequeueDog();
    } else if (dogs_.empty()) {
      return DequeueCat();
    }

    auto cat = cats_.front();
    auto dog = dogs_.front();

    if (cat.id() < dog.id()) {
      cats_.pop();
      return cat;
    } else {
      dogs_.pop();
      return dog;
    }
  }

private:
  std::queue<Cat> cats_;
  std::queue<Dog> dogs_;
  int id_ = 0;
};

TEST(animal_shelter_test, EnqueueCat) {
  auto shelter = AnimalShelter();
  auto c = Cat("cat");
  shelter.Enqueue(c);
  EXPECT_EQ(shelter.DequeueAny().name(), "cat");
}

TEST(animal_shelter_test, EnqueueDog) {
  auto shelter = AnimalShelter();
  auto d = Dog("dog");
  shelter.Enqueue(d);
  EXPECT_EQ(shelter.DequeueAny().name(), "dog");
}

TEST(animal_shelter_test, DequeueAny) {
  auto shelter = AnimalShelter();
  auto d = Dog("dog");
  shelter.Enqueue(d);
  auto c = Cat("cat");
  shelter.Enqueue(c);
  EXPECT_EQ(shelter.DequeueAny().name(), "dog");
  EXPECT_EQ(shelter.DequeueAny().name(), "cat");
}

TEST(animal_shelter_test, DequeueAnyNoCats) {
  auto shelter = AnimalShelter();
  auto d1 = Dog("dog1");
  shelter.Enqueue(d1);
  auto d2 = Dog("dog2");
  shelter.Enqueue(d2);
  EXPECT_EQ(shelter.DequeueAny().name(), "dog1");
  EXPECT_EQ(shelter.DequeueAny().name(), "dog2");
}

TEST(animal_shelter_test, DequeueAnyNoDogs) {
  auto shelter = AnimalShelter();
  auto c1 = Dog("cat1");
  shelter.Enqueue(c1);
  auto c2 = Dog("cat2");
  shelter.Enqueue(c2);
  EXPECT_EQ(shelter.DequeueAny().name(), "cat1");
  EXPECT_EQ(shelter.DequeueAny().name(), "cat2");
}

TEST(animal_shelter_test, DequeueCat) {
  auto shelter = AnimalShelter();
  auto d = Dog("dog");
  shelter.Enqueue(d);
  auto c = Cat("cat");
  shelter.Enqueue(c);
  EXPECT_EQ(shelter.DequeueCat().name(), "cat");
}

TEST(animal_shelter_test, DequeueDog) {
  auto shelter = AnimalShelter();
  auto c = Cat("cat");
  shelter.Enqueue(c);
  auto d = Dog("dog");
  shelter.Enqueue(d);
  EXPECT_EQ(shelter.DequeueDog().name(), "dog");
}
