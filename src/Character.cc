#include <Character/Character.h>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <iostream> 
using namespace character;
using namespace std;



//-------------------------------------------------------------------------------------------
Character::Character() : _type(Type::Knight), health(300), armor(5), damage(56), abilityChance(character:: KnightAbilityChance), abilityScale(1), dodge(0),normal_armor(armor),normal_damage(damage)
{ 
	
}

Character:: Character(const Type type, const float health, const float armor, const float damage, string name) : _type(type), health(health), armor(armor), damage(damage), abilityScale(1), dodge(0), abilityChance(0),name(name), normal_armor(armor), normal_damage(damage)
{
	if (type == Type::Knight)
	{
		abilityChance = character::KnightAbilityChance;
	}
	else if (type == Type::Assasin)
	{
		abilityChance = character::AssasinAbilityChance;
	}
	else if (type == Type::Berserk)
	{
		abilityChance = character:: BerserkAbilityChance;
	}
}

CharacterPtr Character::createKnight(const float health, const float armor, const float damage,string name)
{
	return new Character(Type::Knight, health, armor, damage,name);
}

CharacterPtr Character::createAssasin(const float health, const float armor, const float damage,string name)
{
	return new Character(Type::Assasin, health, armor, damage,name);
}
	
CharacterPtr Character::createBerserk(const float health, const float armor, const float damage,string name)
{
	return new Character(Type::Berserk, health, armor, damage,name);
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
float Character::get_health() const
{
	return health;
}

float Character::get_armor() const
{
	return armor;
}

float Character::get_damage() const
{
	return damage;
}
std::string Character::get_name() const
{
	return name;
}

int Character::get_abilityChance() const
{
	return abilityChance;
}
Type Character::get_type() const
{
	return _type;
}
void Character::set_health(float _health)
{
	health = _health;
}
bool Character::get_abylity_proc() const
{
	return pass_abylity_proc;
}
float Character::get_normal_damage() const
{
	return normal_damage;
}
float Character::get_normal_armor() const
{
	return normal_armor;
}
void Character::set_name(std:: string _name) 
{
	name = _name;
}
void Character::set_armor(float _armor)
{
	armor = _armor;
}

void Character::set_damage(float _damage)
{
	damage = _damage;
}

//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
float Character:: CalcDamage()
{
	if (_type == Type::Berserk)
	{
		pass_abylity_proc = 0;
		int chance = 1 + rand() % 100;
		if (chance <= abilityChance * abilityScale)
		{
			pass_abylity_proc = 1;
			return damage * 3;
		}
		return damage;
	}
	return damage;
}
void Character::Attack(Character& otherHero)
{
	
	pass_abylity_proc = 0;
	otherHero.takeDamage(*this);
	if (_type == Type::Assasin)
	{
		int chance = 1 + rand() % 100;
		if (chance <= abilityChance * abilityScale)
		{
			pass_abylity_proc = 1;
		}
	}
	armor = normal_armor;
	damage = normal_damage;
}
void Character::takeDamage( Character& otherHero)
{

	if (_type == Type::Knight)
	{
		pass_abylity_proc = 0;
		int chance = 1 + rand() % 100;
		if (chance <= abilityChance * abilityScale)
		{
			health -= otherHero.CalcDamage()*((1 - (armor/100))/ 2);
			pass_abylity_proc = 1;
			abilityScale = 1;
		}
		else
		{
			health -=  otherHero.CalcDamage()*(1 - (armor/100));
		}
	}
	else if (_type == Type::Assasin)
	{
		if (dodge)
		{
			
			dodge = 0;
		}
		else
		{
			health -= otherHero.CalcDamage() * (1 - (armor / 100));
		}
	}
	else
	{
		health -= otherHero.CalcDamage() * (1 - (armor / 100));
	}
}

void Character:: ability()
{
	armor = normal_armor;
	damage = normal_damage;
	if (_type == Type::Knight)
	{
		armor = (1.25f * armor) + 2;
		damage = (0.65f * damage);
	}
	else if (_type == Type::Assasin)
	{
		dodge = 1;
	}
	else if (_type == Type::Berserk)
	{
		pass_abylity_proc = 0;
		armor =  (0.5f * armor) + 1;
		damage =  (1.5f * damage);
		abilityScale = 3;
	}
}
CharacterPtr Character::clone() const 
{
	return new Character(_type, health,armor,damage,name);
}

//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
CharacterList::CharacterList() : _size(0), _characters(nullptr)
{

}
CharacterList::CharacterList(const CharacterList& other) : _characters(new CharacterPtr[other._size]),_size(other._size)
{
	for (int i = 0; i < _size; ++i)
	{
		_characters[i] = other[i]->clone();
	}
}

int CharacterList:: size() const
{
	return _size;
}

void CharacterList::insert(CharacterPtr ch, int index)
{	

		auto new_characters = new CharacterPtr[_size + 1];
		for (int i = 0; i <= _size; ++i) 
		{
			if (i == index)
			{
				new_characters[i] = ch;
			}
			else if (i < index)
			{
				new_characters[i] = _characters[i];
			}
			else
			{
				new_characters[i] = _characters[i - 1];
			}
		} 
		delete[] _characters;
		_characters = new_characters;
		++_size;


}
void CharacterList::insert(CharacterPtr hero)
{
	auto new_characters = new CharacterPtr[_size + 1];

	for (int i = 0; i < _size; ++i) {
		new_characters[i] = _characters[i];
	}
	new_characters[_size] = hero;

	delete[] _characters;
	_characters = new_characters;

	++_size;

}
void CharacterList::swap(CharacterList& other) {
	std::swap(this->_characters, other._characters);
	std::swap(this->_size, other._size);
}
void CharacterList::remove(CharacterPtr other) 
{
	bool search = false;
	for (int i = 0; i <= _size; ++i)
	{
		if (_characters[i] == other)
		{
			search = true;
			break;
		}
	}
	if (search)
	{
		auto new_characters = new CharacterPtr[_size - 1];
		bool flag = true;
		for (int i = 0; i < _size; ++i)
		{
			if (_characters[i] != other && flag)
			{

				new_characters[i] = _characters[i];
			}
			else
			{
				flag = false;
				new_characters[i] = _characters[i + 1];
			}
		}
		
		delete _characters;
		_characters = new_characters;
		--_size;

	}
	else
	{
		throw runtime_error("[CharacterList::remove()] object not found");
	}

}
CharacterList& CharacterList:: operator=(const CharacterList& rhs) {
	CharacterList copy(rhs);
	copy.swap(*this);
	return *this;
}
CharacterPtr CharacterList::operator[](const int index) const {
	if (index >= _size || index < 0) {
		throw runtime_error("[CharacterList::operator[] ] invalid index");
	}
	return _characters[index];
}
CharacterList::~CharacterList() {
	for (int i = 0; i < _size; ++i) {
		delete _characters[i];
	}
	delete[] _characters;
}

int CharacterList::index_of_strongest_hero() const
{
	float max_damage = 0.f;
	int index = 0;
	for (int i = 0; i < _size; ++i)
	{
		if (_characters[i]->get_damage() > max_damage)
		{
			max_damage = _characters[i]->get_damage();
			index = i;
		}
	}
	return index;
}
//-------------------------------------------------------------------------------------------




