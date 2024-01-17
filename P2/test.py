import unittest

import aux


# юнит-тесты вспомогательных функций
class TestCase(unittest.TestCase):
    def test_parse_command(self):
        self.assertEqual(aux.parse_command(["python3", "ex1.csv", "ex2.csv"]), 
                         ("ex1.csv", "ex2.csv"))
        self.assertEqual(aux.parse_command(["python3", "ex1.csv"]), 
                         ("ex1.csv", aux.DEFAULT_OUT_CSV))
        self.assertEqual(aux.parse_command(["python3"]), 
                         (aux.DEFAULT_IN_CSV, aux.DEFAULT_OUT_CSV))
        
    def test_init_params(self):
        lines = [["0.0.0.0", "1.1.1.1", 0, 0, 1, 1]]
        self.assertEqual(sorted(aux.init_params(lines)), 
                         [["0.0.0.0", 0, 0, 0, 0], ["1.1.1.1", 0, 0, 0, 0]])
        
        lines = [["0.0.0.0", "1.1.1.1", 0, 0, 1, 1], 
                 ["1.1.1.1", "2.2.2.2", 0, 0, 1, 1], 
                 ["2.2.2.2", "3.3.3.3", 0, 0, 1, 1], 
                 ["3.3.3.3", "0.0.0.0", 0, 0, 1, 1]]
        self.assertEqual(sorted(aux.init_params(lines)), 
                         [["0.0.0.0", 0, 0, 0, 0], ["1.1.1.1", 0, 0, 0, 0],
                          ["2.2.2.2", 0, 0, 0, 0], ["3.3.3.3", 0, 0, 0, 0]])


if __name__ == "__main__":
    unittest.main()
