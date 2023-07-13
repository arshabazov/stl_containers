Этот проект посвящен основным стандартным контейнерам С++, пониманию их работы и работе со стандартом.

Базовая часть:

    Реализовать контейнер std::vector
    Реализовать ассоциативный контейнер std::map
    Реализовать контейнер-адаптер std::stack, по дефолту должен конструироваться на std::vector и быть совместимым с другими контейнерами.
    При проектировании должны быть реализованы:
        std::iterator_traits
        std::reverse_iterator
        std::enable_if (Да это С++11, но НАДО)
        std::is_integral
        std::equal
        std::lexicographical_compare
        std::pair
        std::make_pair