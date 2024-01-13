#from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.common.by import By
from selenium import webdriver
import json

myOptions = webdriver.ChromeOptions()
myOptions.add_argument("headless")
myOptions.add_argument("lang=ko_KR")

driver = webdriver.Chrome(options = myOptions)

URL = 'https://signal.bz/news'
driver.get(url=URL)
driver.implicitly_wait(time_to_wait=5)

date_now = driver.find_element(by=By.XPATH, value='//*[@id="app"]/div/main/div/section/div/section/section[1]/div[1]/div[1]/span')
naver_results = driver.find_elements(By.CSS_SELECTOR, '#app > div > main > div > section > div > section > section:nth-child(2) > div:nth-child(2) > div > div > div > a > span.rank-text')

print("##### 실시간 검색어 #####")
print(date_now.text)

myDict = dict()
myList = list()

count = 1

for naver_result in naver_results:
    myStr = str(count) + "위 " + naver_result.text
    myList.append(myStr)
    count += 1

myDict['topic'] = myList

with open('data.json', 'w', encoding = 'UTF-8') as fp:
    json.dump(myDict, fp, indent = 4, ensure_ascii=False)

driver.quit()