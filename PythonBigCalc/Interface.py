from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5 import uic
import subprocess
import re

class View(QWidget):
	def __init__(self):
		super().__init__()
		
		uic.loadUi('form.ui', self)
	

		#Natural Tab
		self.natNum1.textChanged.connect(self.get_nat_input)
		self.natNum2.textChanged.connect(self.get_nat_input)
		self.natOperatorBox.currentIndexChanged.connect(self.get_nat_input)

		#Integer Tab
		self.intNum1.textChanged.connect(self.get_int_input)
		self.intNum2.textChanged.connect(self.get_int_input)
		self.intOperatorBox.currentIndexChanged.connect(self.get_int_input)

		#Fractions Tab
		self.numerator1.textChanged.connect(self.get_fra_input)
		self.numerator2.textChanged.connect(self.get_fra_input)
		self.denom1.textChanged.connect(self.get_fra_input)
		self.denom2.textChanged.connect(self.get_fra_input)
		self.fraOperatorBox.currentIndexChanged.connect(self.get_fra_input)
		
		#Polynoms Tab
		self.polNum1.textChanged.connect(self.get_pol_input)
		self.polNum2.textChanged.connect(self.get_pol_input)
		self.natOperatorBox_2.currentIndexChanged.connect(self.get_pol_input)


		self.show()

	def get_nat_input(self):
		num1 = self.natNum1.text()
		num2 = self.natNum2.text()
		op = self.natOperatorBox.currentText()
		
		if(num1 and op and num2):
			result = subprocess.run(["DM.exe", "N", num1, op, num2], stdout=subprocess.PIPE)
			result = result.stdout.decode("utf-8")
			self.natResult.setText(result)

	def get_int_input(self):
		num1 = self.intNum1.text()
		num2 = self.intNum2.text()
		op = self.intOperatorBox.currentText()
		
		if(num1 and op and num2):
			result = subprocess.run(["DM.exe", "I", num1, op, num2], stdout=subprocess.PIPE)
			result = result.stdout.decode("utf-8")
			self.intResult.setText(result)

	def get_fra_input(self):
		num1 = self.numerator1.text()
		denom1 = self.denom1.text()  
		
		num2 = self.numerator2.text()
		denom2 = self.denom2.text()

		op = self.fraOperatorBox.currentText()
		
		if(num1 and denom1 and op and num2 and denom2):
			result = subprocess.run(["DM.exe", "F", num1, denom1, op, num2, denom2], stdout=subprocess.PIPE)
			result = result.stdout.decode("utf-8")
		
			result = result.split("/")
			result[1] = result[1].split("=")

			self.resultNumerator.setText(result[0])
			self.resultDenom.setText(result[1][0])
			self.fraResult.setText(result[1][1])

	def pol_to_api(self, pol):
		pattern = "([-]?[ ]?)(\d+\/\d+|\d+)( ?\* ?x ?\^ ?(\d+))?"
		#pattern = [sign, coef, all, power]
		pol_arr = re.findall(pattern, pol)
		pol_arr.sort(key=lambda x: int(x[3] or 0))

		if(pol_arr):
			pol_coefs = ["0 1" for i in range(int(pol_arr[-1][3] or 0) + 1)]

			for sign, coef, full, power in pol_arr:
				num, denom = coef, 1 
				if("/" in coef):
					num, denom = coef.split("/")

				if("-" in sign):
					num = "-" + num

				pol_coefs[int(power or 0)] = "{} {}".format(num, denom)

			result = " ".join(list(reversed(pol_coefs)))
			return result

	def get_pol_input(self):
		
		pol1 = self.polNum1.text()
		pol2 = self.polNum2.text()
		
		op = self.natOperatorBox_2.currentText()

		if(pol1 and pol1[-1] == "*"):
			self.polNum1.setText(pol1 + " x^")

		if(pol2 and pol2[-1] == "*"):
			self.polNum2.setText(pol2 + " x^")

		pol1 = self.pol_to_api(pol1)
		pol2 = self.pol_to_api(pol2)

		if(pol1 and pol2):
			result = subprocess.run(["DM.exe", "P", pol1, op, pol2], stdout=subprocess.PIPE)
			result = result.stdout.decode("utf-8")
			self.polResult.setText(result)

app = QApplication([])
view = View()
app.exec()