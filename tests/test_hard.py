import os
import subprocess
import unittest

from tests import tools

BINARY_NAME = "42sh"


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

        tools.valgrind_wrapper(self.binary, command, True)

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
        cli = ["mkdir", "-p", "%s" % folder, ";", "cd", "%s" % folder, ";", "ls -a"]
        try:
            stdout, stderr = self.execute_my_shell(cli)
            self.assertEqual(stdout[:5], ".\n..\n")
            self.assertEqual(stderr, "")
        finally:
            os.rmdir(folder)

    def test_01_semi(self):
        folder = "%s.d" % self.test_01_semi.__name__

        cli = ["mkdir", "-p", "%s" % folder, ";", "cd", "%s" % folder, ";", "pwd",
               ";", "unsetenv", "OLDPWD", ";", "cd", "-"]
        try:
            stdout, stderr = self.execute_my_shell(cli)
            e_path = os.path.abspath(folder)
            self.assertEqual(stdout[:len(e_path)], e_path)
            self.assertEqual(stderr, "cd: OLDPWD not set\n")
        finally:
            os.rmdir(folder)

    def test_02_semi(self):
        folder = "%s.d" % self.test_02_semi.__name__

        cli = ["mkdir", "-p", "%s" % folder, ";", "ln", "-s", "%s" % folder, "%s.link" % folder, ";"
                                                                                                 "cd", "-L",
               "%s.link" % folder, ";", "pwd -L"]
        try:
            stdout, stderr = self.execute_my_shell(cli)
            e_path = os.path.abspath(folder)
            self.assertEqual(stderr, "")
            self.assertEqual(stdout[:len("%s.link" % e_path)], "%s.link" % e_path)
        finally:
            os.rmdir(folder)
            os.remove("%s.link" % folder)

    def test_03_semi(self):
        folder = "%s.d" % self.test_03_semi.__name__

        cli = ["mkdir", "-p", "%s" % folder, ";", "ln", "-s", "%s" % folder, "%s.link" % folder, ";"
                                                                                                 "cd", "-P",
               "%s.link" % folder, ";", "pwd -L"]
        try:
            stdout, stderr = self.execute_my_shell(cli)
            e_path = os.path.abspath(folder)
            self.assertEqual(stderr, "")
            self.assertEqual(stdout[:len("%s" % e_path)], "%s" % e_path)
        finally:
            os.rmdir(folder)
            os.remove("%s.link" % folder)

    def test_04_semi(self):
        folder = "%s.d" % self.test_04_semi.__name__

        cli = ["mkdir", "-p", "%s" % folder, ";", "ln", "-s", "%s" % folder,
               "%s.link" % folder, ";", "cd", "-P",
               "%s.link" % folder, ";", "pwd -L"]
        try:
            stdout, stderr = self.execute_my_shell(cli)
            e_path = os.path.abspath(folder)
            self.assertEqual(stderr, "")
            self.assertEqual(stdout[:len("%s" % e_path)], "%s" % e_path)
        finally:
            os.rmdir(folder)
            os.remove("%s.link" % folder)
