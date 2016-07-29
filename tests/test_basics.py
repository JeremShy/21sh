import os
import subprocess
import unittest

BINARY_NAME = "21sh"

class TestBasics(unittest.TestCase):
    tests_dir = os.path.split(__file__)[0]
    binary = "%s/../%s" % (tests_dir, BINARY_NAME)
    prompt = ""

    @classmethod
    def setUpClass(cls):
        if os.path.isfile(cls.binary) is False:
            raise IOError("Make the project: %s not here\n" % cls.binary)
        cls.prompt = cls.get_prompt(cls.binary)

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
        return stdout.replace(self.prompt, ""), stderr

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


if __name__ == "__main__":
    unittest.main()
