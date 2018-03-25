from PyQt5.QtWidgets import *
from PyQt5.QtGui import *
from PyQt5.QtCore import *
from PyQt5 import uic
import subprocess

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

app = QApplication([])
view = View()
app.exec()
