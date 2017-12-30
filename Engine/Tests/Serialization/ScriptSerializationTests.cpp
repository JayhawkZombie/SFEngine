////////////////////////////////////////////////////////////
//
// MIT License
//
// Copyright(c) 2017 Kurt Slagle - kurt_slagle@yahoo.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// The origin of this software must not be misrepresented; you must not claim
// that you wrote the original software.If you use this software in a product,
// an acknowledgment of the software used is required.
//
////////////////////////////////////////////////////////////

#include "ScriptSerializationTests.h"

#include <cereal/archives/portable_binary.hpp>
#include <cereal/types/string.hpp>

void RunScriptSerializationTests()
{
  /*
   *  Test1: 
   *    * Base64 encode script source code
   *    * Serialize to file
   *    * Deserialize from file
   *    * Base64 decode script source code
   *    * compile script
   *    * execute & extract vars
   *    
   *  Test2:
   *    * Create bytecode for source code
   *    * Base64 encode bytecode
   *    * Serialize to file
   *    * Deserialize from file
   *    * Base64 decode bytecode
   *    * create script
   *    * execute & extract vars
   **/

  
  std::string source(
    u8R"(
        import core
         
        set testval to 1

        loop x from 1 to 10
          set testval to (testval + ( testval * testval ))
        end
        )"
  );

  /*
   *  Test1
   **/
  {
    std::cout << "*******************************************\nScriptSerialization test 1\n";

    std::string b64_source;

    /* Encode source code as base64 */
    bn::encode_b64(source.begin(), source.end(), std::back_inserter(b64_source));

    std::ofstream file("test1.bin", std::ios_base::binary);

    /* Output to file */
    {
      cereal::PortableBinaryOutputArchive archive(file);

      archive(b64_source);
    }
    file.close();

    /* Read from file */
    
    std::string extracted_source;
    std::ifstream infile("test1.bin", std::ios_base::binary);

    {
      cereal::PortableBinaryInputArchive archive(infile);

      archive(extracted_source);
    }
    infile.close();

    /* Decode base64 source code */
    std::string b64_extracted;

    bn::decode_b64(extracted_source.begin(), extracted_source.end(), std::back_inserter(b64_extracted));

    auto Runtime = Jinx::CreateRuntime();

    auto bcode = Runtime->Compile(b64_extracted.c_str(), "base64_decoded_source_script");

    /*
     *  Dump bytecode data
     **/
    auto bsize = bcode->Size();
    const auto *bptr = bcode->Ptr();

    std::cout << "Bytecode Size: " << bsize << "\n";
    std::cout << "Bytecode Data:\n"
      << "\n------------------------------------\n";
    for (std::size_t i = 0; i < bsize; ++i)
    {
      std::cout << bptr[i];
    }

    std::cout << "\n------------------------------------\n";

    /* Try to run the script */
    auto script = Runtime->CreateScript(bcode);

    if (!script->Execute())
    {
      std::cout << "Test1 script error\n";
    }
    else
    {
      auto val_variant = script->GetVariable("testval");
      if (val_variant.IsInteger())
      {
        auto val_val = val_variant.GetInteger();
        std::cout << "testval = " << val_val << "\n";
      }
    }

  }

  /*
   *  Test2
   **/
  {
    std::cout << "*******************************************\n** ScriptSerialization test 2\n\n\n";

    auto Runtime = Jinx::CreateRuntime();
    auto bcode = Runtime->Compile(source.c_str(), "bycode_serialized_source_script");
    const auto *bcode_ptr = bcode->Ptr();

    /*
    *  Dump bytecode data before serializing
    **/
    {
      auto bsize = bcode->Size();
      const auto *bptr = bcode->Ptr();

      std::cout << "Bytecode Size: " << bsize << "\n";
      std::cout << "Bytecode Data:\n"
        << "\n------------------------------------\n";
      for (std::size_t i = 0; i < bsize; ++i)
      {
        std::cout << bptr[i];
      }

      std::cout << "\n------------------------------------\n";
    }

    std::vector<uint8_t> bcode_vec(bcode->Size());
    std::size_t i = 0;
    for (auto & byte : bcode_vec)
    {
      byte = bcode_ptr[i++];
    }

    /* Serialize vector */

    std::ofstream ofile("test2.bcode", std::ios_base::binary);

    {
      cereal::PortableBinaryOutputArchive archive(ofile);

      archive(bcode_vec);
    }

    ofile.close();

    /* Deserialize bytecode */

    std::ifstream ifile("test2.bcode", std::ios_base::binary);
    std::vector<uint8_t> bvec_deser;

    {
      cereal::PortableBinaryInputArchive archive(ifile);
    
      archive(bvec_deser);
    }
    ifile.close();

    /*
     *  Dump bytecode after Deserializing
     **/
    std::cout << "Bytecode Size: " << bvec_deser.size() << "\n";
    std::cout << "Bytecode Data:\n"
      << "\n------------------------------------\n";
    for (const auto byte : bvec_deser)
    {
      std::cout << byte;
    }
    std::cout << "\n------------------------------------\n";

    /* Pull bytecode data out of vector and read it into a Bytecode object */
    Jinx::BufferPtr buffer = Jinx::CreateBuffer();
    buffer->Write(bvec_deser.data(), bvec_deser.size());

    /* Try to create the script using the bytecode & execute */
    auto script = Runtime->CreateScript(buffer);

    if (!script->Execute())
    {
      std::cout << "Test2 script error\n";
    }
    else
    {
      auto var = script->GetVariable("testval");

      if (var.IsInteger())
      {
        auto val = var.GetInteger();

        std::cout << "testval = " << val << "\n";
      }
    }
  }
}
