#include "nodes.hpp"

// ReceiverPreferences

ReceiverPreferences::ReceiverPreferences(ProbabilityGenerator probability_gen) {
    probability_generator_ = probability_gen;
}

ReceiverPreferences::ReceiverPreferences() {
    probability_generator_ = probability_generator;
}


void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    if (preferences.empty()) {
        preferences[r] = 1;
    } else {
        for (auto& element : preferences) {
            element.second = 1 / preferences.size() + 1;
        }
        preferences[r] = 1 / preferences.size() + 1;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    if (preferences.find(r) != preferences.end()) {
        preferences.erase(r);
        for (auto& element : preferences) {
            element.second = 1 / preferences.size();
        }
    } else {
        throw std::invalid_argument("There is no such receiver");
    }
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    double wylosowane = probability_generator_();
    double suma = 0.0;
    IPackageReceiver* to_return = nullptr;
//TODO sprawdzić poprawnośc tej metody
    for (auto& element : preferences) {
        suma += element.second;
        if (suma > wylosowane) {
            to_return = element.first;
            break;
        }
    }
    return (to_return);
}

// PackageSender

PackageSender::PackageSender(ReceiverPreferences&& receiver) {
    receiver_preferences_ = std::move(receiver);
    buffer_ = std::nullopt;
}

void PackageSender::send_package() {
    if (buffer_.has_value()) {
        IPackageReceiver* receiver = receiver_preferences_.choose_receiver();
        receiver->receive_package(std::move(buffer_.value()));
        buffer_.reset();
    }

}

const std::optional<Package> PackageSender::get_sending_buffer() {
    std::optional<Package> xyz = std::nullopt;
    if(buffer_.has_value()){
        xyz = std::move(buffer_.value());
    }
    return (xyz);

    //return(buffer_.value_or(std::nullopt));
}

void PackageSender::push_package(Package&& to_send) {
    if (buffer_.has_value()) {
        throw std::invalid_argument("Buffer is already full");
    } else {
        buffer_ = std::move(to_send);
    }
}


Ramp::Ramp(ReceiverPreferences&& receiver, ElementID id, TimeOffset di) : PackageSender(std::move(receiver)) {
    id_ = id;
    di_ = di;
    type_ = NodeType::RAMP;
}


void Ramp::deliver_goods(Time t) {
    if ((t == 1) || (t % Ramp::di_ == 1)) {
        PackageSender::push_package(Package());
    }
}



// Implementacja klasy Worker 
//TODO Sprawdzić, poprawić
/* Bufor jest zrobiony jako pole klasy jeszcze w .hpp. Tutaj sprawdzam czy bufor jest wolny i jeśli jest, to wpisuje do niego 
 * produkt z kolejki (tutaj nie wiem czy dobrze rozumiem kolejke i produkt w niej - bo po prostu przypisałem wartość 
 * z unique_ptr, a pewnie zupełnie o coś innego chodzi. Wraz z przypisaniem produktu, przypisuje czas rozpoczęcia przetwarzania 
 * (st_ = t). Następnie sprawdzam czy już skończył przetwarzać produkt. Nie skończył, bo w tym takcie dopiero przypisaliśmy 
 * produkt do bufora i czas startu. Dopiero przy drugim obiegu pierwszy if zostanie pominięty, bo bufor będzie już zajęty i 
 * być może spełnimy już warunek 2. ifa i użyjemy metody z PackageSendera, wyczyścimy bufor i czas rozpoczęcia przetwarzania.
 */
void Worker::do_work(Time t) {
    if (!buffer.has_value()) {
        buffer = q_->pop();
        st_ = t;
    }
    if (t == st_ + pd_) {
        push_package(std::move(buffer.value()));
        buffer.reset();
        st_ = 0;
    }
}

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q, ReceiverPreferences&& receiver)
        : PackageSender(std::move(receiver)) {
    id_ = id, pd_ = pd, q_ = std::move(q);
    type_ = NodeType::WORKER;

}

//Ponieważ większości użytkowników klasy Storehouse nie interesuje to, w jaki sposób dokładnie magazyn przechowuje półprodukty, 
//w jej konstruktorze zdefiniuj odpowiedni argument domyślny dla parametru typu std::unique_ptr<IPackageStockpile> 
//(stwórz inteligentny wskaźnik na nowy obiekt typu PackageQueue; nie ma znaczenia, czy będzie to kolejka FIFO, czy LIFO).
//Jak stworzyć argument domyślny jako nowy obiekt typy PackageQueue???
Storehouse::Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d = std::move(PackageQueue(PackageQueueType::FIFO))) {
  id_ = id,
  d_ = std::move(d);
  type_ = NodeType::STOREHOUSE;
}
