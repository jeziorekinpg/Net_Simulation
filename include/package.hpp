#ifndef NET_SIMULATION_PACKAGE_HPP
#define NET_SIMULATION_PACKAGE_HPP

#include <set>

#include "types.hpp"

/**
 * Ponieważ w myśl założeń projektowych w systemie nie mogą istnieć dwa
 * półprodukty o tym samym ID, konstruktor kopiujący oraz operator przypisania
 * zostały oznaczone jako usunięte.
 *
 * Ponieważ konstruktor przenoszący oraz przenoszący operator przypisania
 * sprawiają, że obiekt przekazany jako odpowiednio argument lub operand
 * przestaje być "poprawny" (nie powinniśmy się do niego odnosić później
 * w programie), możemy ten obiekt zmodyfikować - oznaczyć jako "niepoprawny"
 * poprzez przypisanie mu pewnego szczególnego ID spoza dopuszczalnego zakresu
 * (dla przypomnienia: dopuszczalne ID to liczby całkowite DODATNIE).
 */
class Package {
public:
    Package();

    explicit Package(ElementID id);

    Package(const Package&) = delete;

    Package(Package&&) noexcept;

    Package& operator=(Package&) = delete;

    Package& operator=(Package&&) noexcept;

    ~Package();

    [[nodiscard]] ElementID get_id() const { return id_; }

private:
    static const ElementID BLANK_ID = -1;

    /*
     * Począwszy od C++17 pola statyczne mogą być oznaczane jako `inline`,
     * dzięki czemu moża je inicjalizować wewnątrz definicji klasy (a nie
     * w osobnym pliku źródłowym).
     */

    // Pula identyfikatorów aktualnie przyporządkowanych półproduktom.
    inline static std::set<ElementID> assigned_ids_{0};

    // Pula identyfikatorów, które zostały zwolnione w wyniku usuwania półproduktów.
    inline static std::set<ElementID> freed_ids_;

    ElementID id_ = BLANK_ID;
};

#endif //NET_SIMULATION_PACKAGE_HPP


