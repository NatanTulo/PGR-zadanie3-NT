Zadanie rekrutacyjne do PGRacing Team

# Zarządzanie listą zadań

## Opis projektu
Projekt stanowi prostą aplikację konsolową napisaną w języku C++ umożliwiającą zarządzanie listą zadań. Program oferuje następujące funkcjonalności:
- Dodawanie nowych zadań z walidacją obowiązkowych pól (np. unikalna nazwa zadania).
- Usuwanie zadań z listy, z obsługą błędów, gdy zadanie nie istnieje.
- Wyświetlanie szczegółowych informacji o zadaniach.
- Edycję zadań, w tym zmianę statusu na "Do zrobienia", "W trakcie" lub "Zrobione".

## Funkcjonalności
- **Dodawanie zadań**: Użytkownik wprowadza nazwę (wymagana, unikalna), deadline, opis, tagi oraz przypisanych do zadania.
- **Usuwanie zadań**: Umożliwia usuwanie zadania po podaniu nazwy. Obsłużony jest przypadek nieistniejącego zadania.
- **Edycja zadań**: Pozwala na edycję poszczególnych pól zadania oraz zmianę statusu.
- **Wyświetlanie zadań**: Lista zadań jest prezentowana w czytelny sposób, z wyświetleniem wszystkich przypisanych informacji.

## Walidacja i obsługa wyjątków
- Program nie umożliwia dodania zadania bez nazwy.
- W przypadku próby usunięcia zadania, które nie istnieje, użytkownik otrzymuje komunikat o błędzie.
- Po każdej operacji użytkownik może powrócić do menu głównego.

## Uruchomienie projektu
1. Sklonuj repozytorium lub pobierz pliki projektu.
2. Skonfiguruj środowisko kompilacji dla języka C++.
3. Skompiluj program przy użyciu wybranego kompilatora.
4. Uruchom aplikację w konsoli.

## Podsumowanie
Projekt demonstruje podstawowe techniki zarządzania danymi, walidacji wejścia oraz wykorzystania prostego interfejsu tekstowego do interakcji z użytkownikiem, zapewniając jednocześnie klarowną strukturę i łatwość rozbudowy.
