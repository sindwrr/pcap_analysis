import sys

import aux


def main(argv):
    in_csv, out_csv = aux.parse_command(argv)

    # заносим строки из первого csv в список
    lines = aux.read_csv(in_csv)
    if not lines:
        return

    # инициализируем список в вложенными списками вида:
    # [IP, кол-во принятых пакетов, кол-во принятых байт,
    # кол-во переданных пакетов, кол-во переданных байт]
    params = aux.init_params(lines)

    print("Уникальных IP-адресов:", len(params))

    # вычисляем информацию и пакетах и байтов на основе данных из первого csv
    aux.calculate(params, lines)

    # записываем полученные данные во второй csv
    aux.write_csv(out_csv, params)


if __name__ == "__main__":
    main(sys.argv)
