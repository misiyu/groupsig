#include <iostream>
#include "./algorithm/GroupSig.h"

using namespace std;

int main()
{
	string result ;
	string algorithm_method = "bbs04" ;
	string pbc_param_str = "{\"linear_type\":\"f\", \"bit_len\": 256}" ;
	//create_group_default(result , algorithm_method );
	GroupSigApi::create_group(result , algorithm_method , pbc_param_str);
	cout << "===========================================================" << endl;
	cout << result << endl ;
	cout << "===========================================================" << endl;

	int tmp_i1 = 0;
	int tmp_i2 = result.find('*',tmp_i1) ;
	string gpk = result.substr(tmp_i1 , tmp_i2 - tmp_i1);
	tmp_i1 = tmp_i2+1 ;
	tmp_i2 = result.find('*',tmp_i1);
	string gmsk = result.substr(tmp_i1, tmp_i2 - tmp_i1);
	tmp_i1 = tmp_i2+1 ;
	tmp_i2 = result.find('*',tmp_i1);
	string gamma = result.substr(tmp_i1, tmp_i2 - tmp_i1);
	tmp_i1 = tmp_i2+1 ;
	string pbc_param = result.substr(tmp_i1, result.length()-tmp_i1);

	cout << "===========================================================" << endl;
	cout << "gpk = \n" << gpk << endl ;
	cout << "===========================================================" << endl;
	cout << "gmsk = \n" << gmsk << endl ;
	cout << "===========================================================" << endl;
	cout << "gamma = \n" << gamma << endl ;
	cout << "===========================================================" << endl;
	cout << "pbc_param = \n" << pbc_param << endl ;
	cout << "===========================================================" << endl;

	string gsk ;

	GroupSigApi::group_member_join(gsk , algorithm_method , pbc_param , gmsk , 
			gpk , gamma);

	cout << "===========================================================" << endl;
	cout << "gsk = \n" << gsk << endl ;
	cout << "===========================================================" << endl;

	string sig = "";
	string message = "hello";
	GroupSigApi::group_sig(sig , algorithm_method , gpk , gsk , pbc_param , 
			message);
	cout << "===========================================================" << endl;
	cout << "sig = \n" << sig << endl ;
	cout << "===========================================================" << endl;

	int ret = 1; 
	//sig[20] = 0;
	GroupSigApi::group_verify(ret , message , sig , algorithm_method , gpk , 
			pbc_param) ;

	cout << "===========================================================" << endl;
	cout << "verify result = \n" << ret << endl ;
	cout << "===========================================================" << endl;

	string A ;
	GroupSigApi::open_cert(A , algorithm_method , sig , message , gpk , 
			gmsk , pbc_param);
	cout << "===========================================================" << endl;
	cout << "cert = \n" << cert << endl ;
	cout << "===========================================================" << endl;

	return 0;
}
