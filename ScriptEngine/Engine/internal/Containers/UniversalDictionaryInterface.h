#pragma once

#ifndef UNIVERSAL_DICTIONARY_INTERFACE_H
#define UNIVERSAL_DICTIONARY_INTERFACE_H

#include <unordered_map>
#include <string>
#include <memory>

class UniversalElement {
public:
	UniversalElement(std::shared_ptr<void> data);
	~UniversalElement() {
		data.reset();
	}
	template<class T>
	std::shared_ptr<T> getElement() {
		return std::reinterpret_pointer_cast<T>(data);
	}
private:
	std::shared_ptr<void> data;
};



class UniversalDictionaryInterface {
public:
	template<class ElementType>
	void addElement(ElementType* element);

	template<class ElementType>
	void removeElement(const std::string& name);

	template<class ElementType>
	void freeElement(const std::string& name);

	template<class ElementType>
	std::shared_ptr<ElementType> getElement(const std::string& name);

	template<class ElementType>
	std::unordered_map<std::string, UniversalElement>* getElementsWithType();

	template<class ElementType, class... Args>
	std::shared_ptr<ElementType> makeElement(Args&&... args);

private:
	std::unordered_map<std::string, std::unordered_map<std::string, UniversalElement>> elements;
};

#endif // !UNIVERSALDICTIONARYINTERFACE
