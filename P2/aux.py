import csv


DEFAULT_IN_CSV = "netflow.csv"
DEFAULT_OUT_CSV = "final.csv"


# читает названия файлов из командной строки
def parse_command(argv: list[str]) -> tuple[str, str]:
    in_csv = argv[1] if len(argv) > 1 else DEFAULT_IN_CSV
    out_csv = argv[2] if len(argv) > 2 else DEFAULT_OUT_CSV
    return in_csv, out_csv


# читает данные из csv и заносит в список
# (IP в виде строки, остальное в виде целого числа)
def read_csv(filename: str) -> list:
    try:
        with open(filename, "r", newline="") as inFile:
            reader = csv.reader(inFile, delimiter=",")
            print(f"Файл {filename} успешно прочитан")
            return [[int(i) if "." not in i else i for i in line] 
                    for line in reader]
    except FileNotFoundError:
        print("Ошибка открытия файла на чтение!")
        return []


# инициализирует список с требуемыми параметрами
def init_params(lines: list) -> list:
    return [
        [ip, 0, 0, 0, 0]
        for ip in {ip for line in lines for ip in line if isinstance(ip, str)}
    ]


# вычисляет кол-во пакетов и байт для каждой записи
def calculate(params: list, lines: list) -> None:
    for i in range(len(params)):
        for line in lines:
            if params[i][0] == line[0]:
                params[i][3] += line[4]
                params[i][4] += line[5]
            elif params[i][0] == line[1]:
                params[i][1] += line[4]
                params[i][2] += line[5]


# заносит вычисленные данные в csv
def write_csv(filename: str, params: list) -> None:
    try:
        with open(filename, "w", newline="") as outFile:
            writer = csv.writer(outFile, delimiter=",")
            writer.writerows(params)
        print(f"Данные успешно записаны в {filename}")
    except:
        print("Ошибка открытия файла на запись!")
