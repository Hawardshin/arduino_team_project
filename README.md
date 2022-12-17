# arduino_team_project
#코드 개요
스마트 팩토리를 컨트롤 할 수 있는 코드를 짰습니다. 컴퓨터에서 기구들을 컨트롤 하는 것과 어떤걸 생산할지 결정하고 그에 대한 정보를 저장해두었습니다. 사실상 하나의 팩토리를 컨트롤 하는 머신에 들어가는 운영체제(OS)를 만들도록 계획하였습니다.
따라서 주요한 기능으로 생산할 물체를 객체로 생성하여 저장하고 저장된 값을 이용해 생산을 할 수 있도록 하였고 이를 통해 매번 생산을 할 때마다 바꿔야 하는 귀찮은 설정을 줄일 수 있도록 했습니다.(1 make_object) 
추가적인 기능으로 어떤 생산가능 목록이 있는지 탐색을 해볼 수 있고 그 제품이 어떠한 정보를 가지고 있는지 출력하는 부분 또한 기능으로 있습니다. (2. find_object)
어떤 생산품을 만들지 만들고 그 정보를 확인했다면 이제 그 정보를 바탕으로 팩토리에서 생산하는 기계를 작동시킬 것입니다. (3. opperate machine)
생산 기계를 작동하면서 발생할 수 있는 상황들에 대해서 예외로 처리를 하였습니다. 실제 생산중에 예외적으로 기구를 멈춰야 하는 상황은 많이 있겠지만 저희는 그중에 정전이 되는 경우와 비상 스위치를 누르면 바로 종료가 되도록 설정하였습니다.
저희의 기계는 Emergecy state와 normal state 로 구분됩니다. Emergency State 경우에는 기계의 작동을 멈추고 처음 기계 작동 전 상태로 돌아갑니다. 저희가 비상스위치를 누르거나 또는 정전이 됐다고 감지된 경우 Emergency state로 바뀝니다.
Normal state 로 바꾸고 싶다면 emergency 버튼을 한번 더 눌러줍니다. 기본적으로 기계를 처음 켰을 때 emergency state로 지정해뒀습니다. 한번 버튼을 눌러야 실행이 되도록 하는게 더 낫다고 생각했기 때문입니다. 전체적인 흐름은 이렇게 되며 다음 부분은 코드를 보면서 상세한 설명 진행하겠습니다.

#상세 설명
##semiconductor.h
enum으로 생산할 물품의 종류를 지정해주었습니다. 생산할 물품 즉 객체를 클래스로 만들었습니다. 클래스의 변수는 객체의 이름, 생산하는 시간, 생산 물품 개수, 오브젝트의 성질을 저장하는 변수가 있습니다. 각 변수들은 private에 둬서 캡슐화를 진행해주었습니다.
퍼블릭으로 기본 생성자와 인자를 받아서 쓰는 생성자의 원형을 두고 객체의 타입을 출력하는 함수, 객체의 정보를 출력하는 함수, 그리고 각각의 변수들을 리턴해서 정보를 볼 수 있도록 하였습니다. 이 구조로 짠 이유는 객체를 직접적으로 다루지 않고 함수를 통해서 다루도록 만들었습니다.
그리고 상세한 코드는 cpp파일에 구현했습니다.

##team_project.ino 
첫번째로 term_project.ino파일을 살펴보겠습니다.
저희 스마트팩토리 관리 프로그램은 아두이노가 전원이 켜진 상태를 ON상태로 보는 것이 아니라 직접 ON을 입력을 해주어야만 작동을 시작하도록 했습니다. 그에 따라 default print함수는 ON을 입력해야만 다음 단계로 넘어갈 수 있도록 출력하는 함수입니다. default_print 함수의 구조는 나중에 겪은 문제점과 연관이 있기 때문에 그 파트에서 설명하겠습니다.
사용자가 ON을 입력할 때까지 loop문이 돌고 있어서 기다리고 있으며 ON을 입력하면 다음 단계로 ON이 아닌 다른 것을 입력하면 다시 한번 ON입력을 해야 켜진다는 메시지를 띄우고 ON입력을 기다리게 됩니다.
인터럽트를 넣어주게 되어서 이제 버튼을 누르면 상태를 변경할 수 있도록 인터럽트를 설정 해줬습니다. 이제 버튼을 누르면 상태가 변경되는데 상태를 변경하는 함수가 emergency함수입니다. 처음 상태를 저희는 emergency상태로 해주고 싶기 때문에 처음에 함수를 한번 호출해줍니다. 

##Main_page.cpp
ON을 입력하게 되면 main_page()함수를 타고 들어오게 됩니다. 
만들수 있는 객체는 30개로 설정하고 0번째 객체 배열에 default 객체를 생성을 합니다. 여기서 객체란 저희가 만들 생산품을 뜻합니다. 또한 계속해서 이상한 값을 입력을 하면 기계를 off시켜버리도록 코드를 설정했습니다. ON상태에 들어오게 되면 계속해서 입력을 기다리고 있고 Serial입력이 들어오는 경우에만 다음 단계로 넘어가게 됩니다.
사용자가 어떤 행동을 할지는 입력 받은 Case숫자에 따라서 결정됩니다.
처음에 각 선택지를 start_first_print(); 함수를 통해서 출력해줍니다. 각각의 선택지에서 코드가 하는 행동은 다음과 같습니다.
Case 1 : 만약 객체가 30개가 넘어가게 된다면 더이상 생성을 할 수 없도록 했습니다. 그리고 make_new_object( ) 함수를 사용해서 객체를 생성합니다. 여기서 객체를 생성할 때 시리얼 함수로 입력을 받으며 받은 입력을 생성자에 넣어서 생성하는 방식을 사용합니다.
Case 2 : 저희가 객체를 만들지 않았다면 생성할 객체가 없으므로 객체가 없다는 메시지를 출력하고 다음으로 넘어갑니다. 만약 하나 이상의 객체가 있는경우 객체의 탐색으로 넘어가게 됩니다.
Case 3 : 객체를 생성하는 게 끝나고 이제 만든 객체를 바탕으로 스마트팩토리로 생산을 하게 됩니다.
Case 4 : 기계를 종료합니다. 처음 시작할 때의 화면으로 돌아가게 됩니다.
Default : 이제 다른 입력을 하는 경우에 다시한번 입력하라는 창이 뜨면서 입력을 얼마나 했는지 카운트를 합니다. 만약 5번을 실패헀다면 뭔가 입력받는 입력기(여기서는 키보드) 에 문제가 생긴것으로 판단하고 에러 메시지를 띄우고 기계를 종료합니다.

##make_object.cpp (Case 1)
코드가 길어 몇가지 설명이 필요한 코드를 제외하고 직관적으로 볼 수 있는 코드는 문서의 크기가 너무 커져 문서에서 뺐습니다.
1을 입력했을 때 케이스입니다.1번을 입력하면 make_new_object(); 함수로 들어오게 되는데, 객체를 만들어서 리턴해주는 함수입니다. 비슷한 부분이 많은 함수는 문서에서 지우고 넣었습니다. 객체에 넣고 싶은 정보를 입력 받는 함수를 만들어서 각각의 정보를 입력 받았습니다. 그 함수 중 input_quantity같은 경우 서보모터가 최대 180도까지 밖에 못 돌기 때문에 개수를 18개로 제한을 뒀습니다. 만약 모터가 회전에 제한이 없는경우 제한을 두지 않은 것이고 도는 각도를 10도가 아닌 더 낮은 값으로 하면 1~17개로 제한을 두지 않았을 것입니다. 
그리고 객체의 속성을 적는 부분 역시 불가능한 값이 오면 다시 받도록 설정을 해주었습니다.
그렇게 입력을 받아서 클래스를 인스턴스화 하면서 생성자를 호출해서 함께 넣어주도록 구현 후 그 객체를 리턴 하였습니다.

##find_object.cpp (Case 2)
2를 입력하게 되면 함수 void  choose_object(semiconductor *obj,int obj_num) 함수로 들어오게 됩니다. 이 함수는 인자로는 오브젝트 객체들을 담고있는 배열을 인자로 넘겨주게 되면서 객체의 총 개수를 함께 넘겨주게 됩니다. 여기서도 여려 개로 분기가 되는데 입력을 받는데 문자열이 default를 입력하면 저희가 기본으로 생성한 객체에 대한 정보를 보여주고 back을 입력하면 이전 메뉴로 돌아가게 됩니다. 그 외의 입력을 받는경우 find_obj (obj, find_name,obj_num); 오브젝트 배열과 받은 입력과 총 개수를 받아서 입력 받은 문자열의 해당하는 이름을 가진 걸 찾은경우 그 인덱스를 리턴하고 아닌 경우 -1을 리턴 해서 객체가 없다고 출력을 해줍니다.
여기서 원하는 정보를 다 얻고 나면 back을 입력해서 원래의 화면으로 돌아갑니다.

##opperate.cpp (Case 3)
이 파일에는 비상버튼을 누르는 경우 발생하는 인터럽트를 처리하는 함수 + 조도센서 객체를 초기화 하는 함수 하드웨어를 구동하는 파트 등이 있습니다. 코드가 길어 파트별로 나누어 코드 설명 진행하겠습니다.
###part 1(서보모터 선언 및 상태 변경 함수)
가장 위 전역변수로 Servo를 선언합니다. 여기서 Servo 2개는 Servo Penservo; Servo Rotateservo; 이고 이 두개는 각각 위에서 로봇팔과 같은 생산에 사용되는 로봇을 의미하며 그것은 Penservo이고 아래쪽 판인 Rotateservo 같은 경우 실제 스마트 팩토리의 경우에는 컨베이어 벨트 또는 자동화가 가능하도록 되는 파이프라인입니다. 그리고 각각 조도센서 객체를 생성합니다. 조도 센서 클래스는 CDS.h와 CDS.cpp파일에 있습니다. 간단하게 클래스 설명을 하고 넘어가자면 조도센서 클래스에서 update를 호출하면 각 조도센서가 현재의 밝기를 측정해서 밝기 값이 INTEN값보다 낮아지게 되면 state를 1로 변경해서 암전이 됐다는걸 확인합니다. 그리고 상태를 변경하는 함수로 처음 시작할 때 실행 했던 함수인 emergency가 여기 있는데 이 함수는 현재의 state를 읽어서 현재가 emergency 상태라면 normal로 변경해주고 normal상태라면 emergency로 변경해주는 함수입니다. 
###part 2(모터 구동 함수 및 상태확인 함수)
모터 구동함수를 move_rotate경우자동화 기계에서 컴베이어 벨트에 해당하는데 이 부분은 10도로 고정해두고 객체의 개수만큼 회전을 합니다. Move_pen()함수의 경우 저희가 만드는 생산품에 생산에 드는 시간을 입력 받아서 그 시간만큼 시간이 들 수 있도록 순차적으로 10개의 분기로 나눠서 딜레이값을 10으로 나눈후 그만큼의 속도가 걸릴 수 있도록 해줬습니다. 또한 중간중간 state를 확인해주는 부분이 있는데 인터럽트가 발생하면 state값이 변경이 되어서 바로 원래의 위치로 돌아가고 현재의 작동을 중지할 수 있도록 해줬습니다.
그리고 check_state함수 같은 경우는 암전됐는지만 주기적으로 확인해주기 위해 선언된 함수인데 암전이 된 경우를 두개의 조도센서가 모두 어두워 지는 경우와 작동이 끝나고 기다리는 상태에서 update를 했을 때 둘 다 조도 값이 낮게 밝혀진 경우 정전으로 생각하는 걸 코드로 구현 했습니다. 한쪽만 어둡거나 잠깐의 반응에도 민감하게 반응하는 인터럽트로 처리할 경우 사람이 지나가기만 해도 기계가 정지할 수 있기 때문에 일부로 이런식으로 코드를 구현하였습니다.
###part 3(어떤 객체를 구동시킬지 선택 후 구동하는 코드)
3번 분기로 들어오려면 operate_machine(obj, obj_num) 함수를 통해 들어오게 되는데 여기서 저희는 작동시키고 싶은 객체를 선택을 하게 됩니다. 처음에는 기계가 현재 emergency상태라면 물론 LED로 보여주긴 하지만 한번 더 serial에 현재 상태가 emergency이니 버튼을 한번 눌러야 작동이 가능하다고 알려줍니다.
지금까지 만든 모든 객체를 이름과 각각을 인덱스로 출력을 해줍니다. 기계를 작동 시키는 부분이기 때문에 어떤 객체를 선택했는지 그게 맞는지 확인을 하고 아니라고 하는 경우 돌아가게 까지 만들었습니다.
객체를 선택하는 경우 main_operate함수로 들어오게 되는데 몇 개의 객체를 생성했는지를 출력해주면서 인터럽트 등의 문제를 이 부분에서 처리해주게 됩니다.
### 기타부분
추가적으로 print_message부분과 헤더파일 같은 경우는 코드의 설명이 필요없이 출력을 해주는 부분과 각각 사용한 함수를 파일별로 정리하여 헤더파일에 함수원형을 다 적어줬습니다.
#겪은 문제점
##출력하는 문자열이 많아 용량이 부족해지는 현상 발생
사용자가 사용하기 편한 프로그램을 만들기 위해서 저희가 제작한 프로그램은 상당히 많은 문자열을 사용을 했습니다. 하지만 그에 따라서 용량이 99%까지 차서 실행을 하면 계속해서 메시지를 출력하지 못하고 예상치 못한 방향으로 프로그램이 작동을 계속 했습니다.
이 부분에 대한 설명을 하겠습니다.
코드 상세설명에서 나중에 다루기로 한 default_print함수의 모양은 다음과 같습니다.
void  default_print()
{
  char  temp;
  for(int i=0; i < strlen_P(default_meseage); i++){
    temp = pgm_read_byte_near(default_meseage+i);
    Serial.print(temp);
  }
}

이 코드는 print_message.cpp파일에 있고 default_meseage는 전역변수로 
const PROGMEM char default_meseage[] ="\n----------------------------------------------------\nTHE MACHINE IS NOT ON\nYou can input 'ON' then the Machine start to begin\n\n----------------------------------------------------\n";
auto_system.h파일에 들어있습니다.
그냥 println해서 한번에 출력하면 된다고 생각하실 수 있는데 이렇게 한 이유는 아두이노 보드상 메모리 크기 문제 때문입니다. 기본적으로 Serial.println(“문장”); 을 하게 되면 문장의 크기만큼 dynamic메모리 부분이 할당 되는데 이 부분은 Sram영역으로 저희가 사용하는 아두이노 보드에서는 모든 문장을 출력할 수 없었고 그에 따라 출력이 깨지는 현상이 발생했습니다. 이 문제를 해결하기 위해 보드를 새로 살것도 고민을 했지만 단순히 크기 문제 때문에 새로운 보드를 사는 것보다 더 좋은 방법을 찾던 중 저장 공간을 바꾸는 방법을 찾았습니다. 전역 문자열로 const PROGMEM char name[] = “문자열” 이런 모양으로 입력해주면 문자열이 저장되는 방법이 기존에 Sram에 입력되는 것이 아니라 더 용량이 큰 flash메모리에 저장이 되게 됩니다. 이렇게 긴 문자열들의 경우 저장방식을 바꿔서 메모리적으로 더 나은 방식을 사용했습니다.
즉 flash메모리는 변경이 되지 않는 변수를 넣어놓기 적합하고 Sram은 변경되는 메모리를 넣어두기 적합하다고 판단해 긴 문장들은 거의 다 위와 같은 방식으로 print 하였습니다.
##예상되지 않는 입력에 대한 처리
예외 처리는 프로그래머로서 중요시되는 소양이라고 생각됩니다. 만약 유저가 이상한 값을 입력해서 갑자기 기계가 꺼져버리고 고장나버린다면 아무리 잘 만든 기계더라도 사용을 하지 못하기 때문입니다. 더군다라 하드웨어가 연결된 기계를 제어하는 프로그램에서는 특히 이상한 입력에 대해서 handing을 해주지 않는다면 고가의 기계(여기서는 스마트팩토리 설비 또는 로봇팔 등 생산기계)들이 고장날 위험 뿐 아니라 인명피해까지 발생할수 있기 때문에 Exception Handling 에 신경을 썼습니다. Serial입력으로 이상한 값을 입력하는 경우 다시 원래 입력하라는 메시지를 출력하기도 하고 숫자를 입력해야 하는데 문자를 입력하는 경우에 대해서 프로그램이 꺼지거나 죽지 않도록 처리하였습니다.
##서보모터를 처음 구동을 시작할 때 확 돌아가는 문제해결
서보모터를 처음 켜는 경우 돌아가는 문제가 있었는데 이 부분에 대해서 고민을 하다가 코드를 처음 실행할 때 서보모터를 초기 값인180도로 이동 시킬 수 있도록 emergency 함수에 서보값을 초기화 하는 부분을 추가해 해결하였습니다.
##헤더파일에 전역변수 선언 문제
아두이노 내부에서 헤더파일에 전역변수로 선언을 해서 처음에 코드를 사용하였습니다. 하지만 직접 컴파일을 해보고 구동을 하려고 하니 여러 번 전역변수가 선언된다는 문제가 발생해서 전역변수는 각각의 cpp파일에 선언을 하고 전역변수를 사용하는 부분을 한 파일에 묶어줬습니다.
##함수 모듈화 및 파일 분리
코드를 짜며 아무래도 같은 메시지를 출력하는 부분이 많고 여러 번 사용하는 함수가 많아 함수화를 많이 진행하였습니다. 그리고 클래스를 헤더파일로 나누고 각 파일에 맞게 변수명을 수정하면서 앞으로는 더 직관적으로 파일명을 지어야겠다고 느꼈고 조금 더 깔끔하게 코드가 변하게 됐습니다.