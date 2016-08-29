import os
import subprocess
import unittest

BINARY_NAME = "21sh"


class TestAdvanced(unittest.TestCase):
    tests_dir = os.path.split(__file__)[0]
    binary = "%s/../%s" % (tests_dir, BINARY_NAME)
    prompt = ""
    dev_null = None

    @classmethod
    def setUpClass(cls):
        os.write(1, "\nRunning %s\n" % __file__)
        if os.path.isfile(cls.binary) is False:
            raise IOError("Make the project: %s not here\n" % cls.binary)
        cls.prompt = cls.get_prompt(cls.binary)
        cls.dev_null = open("/dev/null", 'w')

    @classmethod
    def tearDownClass(cls):
        cls.dev_null.close()
        os.write(1, "\n")

    @staticmethod
    def get_prompt(binary):
        cmd_list = ["/bin/echo", "-n"]
        p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)
        p_minishell = subprocess.Popen(
            ["%s" % binary], stdin=p_command.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p_command.stdout.close()
        stdout, stderr = p_minishell.communicate()
        return stdout

    def execute_my_shell(self, command):
        """
        Here my shell
        :param command: list of command like ["/bin/ls", "-l"]
        :return:
        """
        cmd_list = ["/bin/echo", "-n"] + command
        p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)
        p_minishell = subprocess.Popen(
            ["%s" % self.binary], stdin=p_command.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p_command.stdout.close()
        stdout, stderr = p_minishell.communicate()

        stdout = stdout.replace("%s\n" % self.prompt, "")
        stdout = stdout.replace("%s" % self.prompt, "")

        return stdout, stderr

    @staticmethod
    def execute_real_shell(command):
        """
        Here the real shell
        :param command: list of command like ["/bin/ls", "-l"]
        :return:
        """
        cmd_list = ["/bin/echo"] + command
        p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE)
        p_real_shell = subprocess.Popen(
            ["/bin/bash"], stdin=p_command.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p_command.stdout.close()
        stdout, stderr = p_real_shell.communicate()
        return stdout, stderr.replace("/bin/bash: line 1: ", "")  # because of bash piping

    def compare_shells(self, command):
        real_std = self.execute_real_shell(command)
        my_std = self.execute_my_shell(command)
        self.assertEqual(real_std, my_std)

    def test_00_prompt_is_removed(self):
        stdout, stderr = self.execute_my_shell([""])
        self.assertEqual("", stdout)
        self.assertEqual("", stderr)

    def test_00_semi(self):
        folder = "%s.d" % self.test_00_semi.__name__
        cli = ["mkdir", "-p", "%s" % folder, ";", "cd", "%s" % folder, ";", "pwd"]
        try:
            self.compare_shells(cli)
        finally:
            os.remove(folder)

    def test_01_semi(self):
        folder = "%s.d" % self.test_01_semi.__name__
        cli = ["mkdir", "-p", "%s" % folder, ";", "cd", "%s" % folder, ";", "pwd",
               ";", "unsetenv", "OLDPWD", ";", "cd", "-"]
        try:
            self.compare_shells(cli)
        finally:
            os.remove(folder)

    def test_02_semi(self):
        folder = "%s.d" % self.test_02_semi.__name__
        cli = ["mkdir", "-p", "%s" % folder, ";", "cd", "%s" % folder, ";", "pwd",
               ";", "setenv", "OLDPWD", "/InexistantFile", ";", "cd", "-"]
        try:
            self.compare_shells(cli)
        finally:
            os.remove(folder)

    def test_03_semi(self):
        cmd = ["cd", "/tmp", ";", "cd", "-"]
        cli = []
        for i in range(50):
            if i > 0:
                cli.append(";")
            for k in cmd:
                cli.append(k)
        self.compare_shells(cli)

    def test_00_fd(self):
        command = [" /bin/cat test_04_nothere 2>&1 | cat -e | rev"]
        self.compare_shells(command)

    def test_03(self):
        command = [" cat test_03_nothere 2>&- "]
        self.compare_shells(command)

    def test_04(self):
        command = [" /bin/cat test_04_nothere 2>&1 "]
        self.compare_shells(command)

    def test_05(self):
        command = [" /bin/cat test_04_nothere 2>&1 | cat -e | rev"]
        self.compare_shells(command)

    def test_06(self):
        command = [" /bin/ls notherefile |& cat -e"]
        self.compare_shells(command)

    def test_07(self):
        command = [" /bin/ls notherefile . |& cat -e"]
        self.compare_shells(command)

    def test_08(self):
        command = [" /bin/ls notherefile . 2>&1 |& cat -e"]
        self.compare_shells(command)

    def test_09(self):
        command = [" /bin/ls notherefile . 2>&1 |& cat -e  | cat -e |& cat -e"]
        self.compare_shells(command)

    def test_10(self):
        command = ["/bin/ls notherefile . 2>&1|&cat -e|cat -e|&cat -e"]
        self.compare_shells(command)

    def test_11(self):
        command = ["/bin/ls notherefile 2>&1|&cat -e|cat -e|&cat -e"]
        self.compare_shells(command)

    def test_12(self):
        command = ["/bin/ls notherefile|&cat -e|cat -e|&cat -e"]
        self.compare_shells(command)

    def test_13(self):
        command = ["/bin/ls -l notherefile .|&cat -e|cat -e|&cat -e|rev|sort|rev"]
        self.compare_shells(command)

    def test_18(self):
        cmd_list = ["/bin/cat", "/dev/urandom"]
        p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE, stderr=self.dev_null)
        runner = [BINARY_NAME]
        p_shell = subprocess.Popen(
            runner, stdin=p_command.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p_command.stdout.close()
        stdout, stderr = p_shell.communicate()
        self.assertEqual('', stdout)

    def test_20(self):
        string_data = \
            "Pandente itaque viam fatorum sorte tristissima, " \
            "qua praestitutum erat eum vita et imperio spoliari, " \
            "itineribus interiectis permutatione iumentorum emensis " \
            "venit Petobionem oppidum Noricorum, ubi reseratae sunt " \
            "insidiarum latebrae omnes, et Barbatio repente apparuit comes, " \
            "qui sub eo domesticis praefuit, cum Apodemio agente in rebus milites " \
            "ducens, quos beneficiis suis oppigneratos elegerat imperator certus " \
            "nec praemiis nec miseratione ulla posse deflecti."

        fd = open("big_data", "a")
        fd.write("echo ")
        s = os.stat('big_data')

        while s.st_size < 107374182L:
            for i in xrange(100):
                fd.write("%d->%s\n" % (i, string_data * i))
            s = os.stat('big_data')
        fd.close()
        cmd_list = ["/bin/cat", "big_data"]
        p_command = subprocess.Popen(cmd_list, stdout=subprocess.PIPE, stderr=self.dev_null)
        runner = [BINARY_NAME]
        p_shell = subprocess.Popen(
            runner, stdin=p_command.stdout, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        p_command.stdout.close()
        stdout, stderr = p_shell.communicate()
        os.remove("big_data")
        self.assertEqual('', stdout)
        self.assertEqual('ERROR max number of characters inside the buffer\n', stderr)
