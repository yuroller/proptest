#include <rapidcheck.h>

#include <algorithm>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include <cctype>

#define TEST 7
#define IMPL 8

/*
Data una lettera, creare un rombo che comincia per 'A' con la
lettera fornita nel punto piu' ampio.

Per esempio: crea_rombo 'C' fornisce

"  A  "
" B B "
"C   C"
" B B "
"  A  "
*/

///////////////////////////////////////////////////////////////////////////
// Soluzione basata su
// https://blog.ploeh.dk/2015/01/10/diamond-kata-with-fscheck/
///////////////////////////////////////////////////////////////////////////

static size_t dimensione_rombo(char l)
{
    return (static_cast<size_t>(l) - 'A') * 2 + 1;
}

static std::vector<std::string> crea_rombo(char l)
{
#if IMPL == 0
    return std::vector<std::string>();
#elif IMPL == 1
    return std::vector<std::string> { "Avvocato del diavolo" };
#elif IMPL == 2
    return std::vector<std::string> { "    A  "};
#elif IMPL == 3
    return std::vector<std::string> { "    A    "};
#elif IMPL == 4
    // BAD: implementazione basata sul test
    // "A"
    // "B"
    // "A"
    std::vector<std::string> rombo;
    for (char c = 'A'; c <= l; ++c) {
        rombo.push_back(std::string(1, c));
    }

    for (char c = l - 1; c >= 'A'; --c) {
        rombo.push_back(std::string(1, c));
    }

    return rombo;
#elif IMPL == 5
    // "  A  "
    // "BBBBB"
    // "CCCCC"
    // "BBBBB"
    // "  A  "
    
    auto dimensione = dimensione_rombo(l);
    std::vector<std::string> rombo;
    std::string linea_a(dimensione, ' ');
    linea_a[dimensione / 2] = 'A';
    
    rombo.push_back(linea_a);
    
    for (char c = 'B'; c <= l; ++c) {        
        rombo.push_back(std::string(dimensione, c));
    }

    for (char c = l - 1; c >= 'B'; --c) {
        rombo.push_back(std::string(dimensione, c));
    }

    if (dimensione > 1) {
        rombo.push_back(linea_a);
    }

    return rombo;

#elif IMPL == 6
// "  A  "
// "B   B"
// "C   C"
// "B   B"
// "  A  "

auto dimensione = dimensione_rombo(l);
std::vector<std::string> rombo;
std::string linea_a(dimensione, ' ');
linea_a[dimensione / 2] = 'A';

rombo.push_back(linea_a);

auto linea_interna = [dimensione](char lettera) {
    std::string s(dimensione, ' ');
    s[0] = lettera;
    s[dimensione - 1] = lettera;
    return s;
};

for (char c = 'B'; c <= l; ++c) {
    rombo.push_back(linea_interna(c));
}

for (char c = l - 1; c >= 'B'; --c) {
    rombo.push_back(linea_interna(c));
}

if (dimensione > 1) {
    rombo.push_back(linea_a);
}

return rombo;

#elif IMPL == 7
// "  A  "
// "B   B"
// "C   C"
// " B B "
// "  A  "

auto dimensione = dimensione_rombo(l);
std::vector<std::string> rombo;
std::string linea_a(dimensione, ' ');
linea_a[dimensione / 2] = 'A';

rombo.push_back(linea_a);

auto linea_interna_superiore = [dimensione](char lettera) {
    std::string s(dimensione, ' ');
    s[0] = lettera;
    s[dimensione - 1] = lettera;
    return s;
};

for (char c = 'B'; c <= l; ++c) {
    rombo.push_back(linea_interna_superiore(c));
}

auto linea_interna_inferiore = [dimensione, l](char lettera) {
    std::string s(dimensione, ' ');
    size_t pos = static_cast<size_t>(l) - lettera;
    s[pos] = lettera;
    s[dimensione - 1 - pos] = lettera;
    return s;
};

for (char c = l - 1; c >= 'B'; --c) {
    rombo.push_back(linea_interna_inferiore(c));
}

if (dimensione > 1) {
    rombo.push_back(linea_a);
}

return rombo;

#elif IMPL == 8
// "  A  "
// " B B "
// "C   C"
// " B B "
// "  A  "

auto dimensione = dimensione_rombo(l);
std::vector<std::string> rombo;

auto linea_rombo = [dimensione, l](char lettera) {
    std::string s(dimensione, ' ');
    size_t pos = static_cast<size_t>(l) - lettera;
    s[pos] = lettera;
    s[dimensione - 1 - pos] = lettera;
    return s;
};

for (char c = 'A'; c <= l; ++c) {
    rombo.push_back(linea_rombo(c));
}

for (char c = l - 1; c >= 'A'; --c) {
    rombo.push_back(linea_rombo(c));
}

return rombo;
#endif
}

///////////////////////////////////////////////////////////////////////////
// Funzioni di utilita
///////////////////////////////////////////////////////////////////////////

static void stampa(const std::vector<std::string>& v)
{
    for (const auto& s: v) {
        std::cout << s << '\n';
    }
}

static std::string trim(std::string s)
{
    // ltrim
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));

    // rtrim
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end()); // base() ritorna un forward_iterator compatibile con s.end() 

    return s;
}

static size_t conta_spazi_iniziali(const std::string& s)
{
    return std::distance(s.begin(),
        std::find_if(s.begin(), s.end(),
        [](int ch) {
            return !std::isspace(ch);
        }));
}

static size_t conta_spazi_finali(const std::string& s)
{
    return std::distance(
        std::find_if(s.rbegin(), s.rend(),
        [](int ch) {
            return !std::isspace(ch);
        }).base(),
        s.end());
}

///////////////////////////////////////////////////////////////////////////
// Test
///////////////////////////////////////////////////////////////////////////

int main()
{
#if 0
    rc::check("Rombo non vuoto (BAD: specifiche dicono solo A-Z)",
        [](const char l) {
            return !crea_rombo(l).empty();
        });

    rc::check("Rombo non vuoto (BAD: troppi fallimenti nelle precondizioni)",
        [](const char l) {
            RC_PRE('A' <= l && l <= 'Z');
            return !crea_rombo(l).empty();
        });
#endif

    // usiamo un generatore
    auto gen = rc::gen::inRange('A', static_cast<char>('Z'+1));
    auto gen2 = rc::gen::inRange('B', static_cast<char>('Z'+1));

    rc::check("Rombo non vuoto",
        [&gen]() {
            return !crea_rombo(*gen).empty();
        });

#if 0
    rc::check("Numero di righe dispari (BAD: non utile, in quanto la soluzione passa il test)",
        [&gen]() {
            return (crea_rombo(*gen).size() % 2) != 0;
        });
#endif

#if TEST > 0
    rc::check("Prima riga contiene A",
        [&gen]() {
            return trim(crea_rombo(*gen).at(0)) == "A";
        });

    rc::check("Ultima riga contiene A",
        [&gen]() {
            auto rombo = crea_rombo(*gen);
            return trim(rombo.at(rombo.size() - 1)) == "A";
        });
#endif

#if TEST > 1
    rc::check("Tutte le righe hanno un contorno simmetrico",
        [&gen]() {
            auto rombo = crea_rombo(*gen);
            return std::all_of(rombo.begin(), rombo.end(),
                [](const std::string& linea) {
                    return conta_spazi_iniziali(linea) == conta_spazi_finali(linea);
                });
        });
#endif

#if TEST > 2
    rc::check("Prima lettera in pattern A..l..A",
        [&gen]() {
            auto l = *gen;
            // RC_TAG(l);
            auto rombo = crea_rombo(l);

            std::string sequenza;
            std::transform(rombo.begin(), rombo.end(),
                std::back_inserter(sequenza),
                [](const std::string& linea) {
                    return trim(linea).at(0);
                });

            auto dimensione = dimensione_rombo(l);
            std::string atteso(dimensione, ' ');
            std::iota(
                atteso.begin(),
                std::next(atteso.begin(), (dimensione + 1) / 2),
                'A');
            std::iota(
                atteso.rbegin(),
                std::next(atteso.rbegin(), (dimensione + 1) / 2),
                'A');

            return atteso == sequenza;
        });
#endif

#if TEST > 3
    rc::check("Altezza == Larghezza",
        [&gen]() {
            auto rombo = crea_rombo(*gen);
            auto altezza = rombo.size();
            return std::all_of(rombo.begin(), rombo.end(),
                [altezza](const std::string& linea) {
                    return linea.size() == altezza;
                });
        });
#endif

#if TEST > 4
    rc::check("Ogni riga, tranne la prima e l'ultima, contiene due lettere uguali",
        [&gen2]() {
            auto rombo = crea_rombo(*gen2);
            //RC_PRE(rombo.size() > 1); // non interessano i rombi degeneri
            return std::all_of(std::next(
                rombo.begin()),
                std::prev(rombo.end()),
                [](std::string linea) {
                    // Erase-remove idiom
                    linea.erase(
                        std::remove(linea.begin(), linea.end(), ' '),
                        linea.end());
                    bool contiene_due_lettere = linea.size() == 2;
                    std::sort(linea.begin(), linea.end());
                    bool contiene_la_stessa_lettera
                        = std::distance(
                            linea.begin(),
                            std::unique(linea.begin(), linea.end()));
                    return contiene_due_lettere && contiene_la_stessa_lettera;
                });
        });
#endif

#if TEST > 5
    rc::check("Il numero di spazi iniziali nella parte inferiore del rombo sono la sequenza 0, 1, 2, ...",
        [&gen]() {
            auto l = *gen;
            auto rombo = crea_rombo(l);
            size_t dimensione_inferiore = static_cast<size_t>(l) - 'A' + 1;
            std::vector<size_t> numero_spazi_rombo(dimensione_inferiore, 0);
            std::transform(std::next(rombo.begin(), rombo.size() / 2), rombo.end(),
                numero_spazi_rombo.begin(), conta_spazi_iniziali);
            std::vector<size_t> numero_spazi_attesi(dimensione_inferiore, 0);
            std::iota(numero_spazi_attesi.begin(), numero_spazi_attesi.end(), 0);
            return std::equal(numero_spazi_attesi.begin(),
                numero_spazi_attesi.end(),
                numero_spazi_rombo.begin());
        });
#endif

#if TEST > 6
    rc::check("Simmetria orizzontale",
        [&gen]() {
            auto l = *gen;
            auto rombo = crea_rombo(l);
            return std::equal(
                rombo.begin(),
                std::next(rombo.begin(), rombo.size() / 2),
                rombo.rbegin());
        });
#endif

    stampa(crea_rombo('E'));
    return 0;
}
